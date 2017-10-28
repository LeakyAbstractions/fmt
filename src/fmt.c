/**
 *
 * @file        fmt.c
 *
 * fmt source code file
 *
 * @version     1.5.0
 * @author      Copyright (c) 2017 Guillermo Calvo
 *
 */

# include "fmt.h"

# include <stddef.h>
# include <stdint.h>
# include <string.h>

# if __STDC_VERSION__ >= 199901L
#   define LONG_LONG_INT        long long int
# else
#   define inline
#   define LONG_LONG_INT        long int
#endif

# ifndef FMT_MAX_FORMATTERS
#   define FMT_MAX_FORMATTERS   16
# endif

# ifndef FMT_MAX_FORMAT_LENGTH
#   define FMT_MAX_FORMAT_LENGTH 255
# endif

# define PARAM_MARK             '%'
# define PARAM_BEGIN            '{'
# define PARAM_META             '*'
# define PARAM_INDIRECT         '@'
# define PARAM_OPTIONS          ':'
# define PARAM_END              '}'

# define HASH(ID)               ( (int)strlen(ID) )
# define IS_FILE(OUT)           ( (OUT)->file   != NULL )
# define IS_BUFFER(OUT)         ( (OUT)->buffer != NULL )
# define HAS_BYTES(OUT)         ( (OUT)->bytes > 0 )
# define IS_READY(OUT)          ( (OUT) != NULL && ( IS_FILE(OUT) || ( IS_BUFFER(OUT) && HAS_BYTES(OUT) ) ) )
# define IS_NUMBER(CHAR)        ( (CHAR) >= '0' && (CHAR) <= '9' )
# define SKIP_NUMBERS(PTR)      while( IS_NUMBER(*(PTR)) ) (PTR)++

# define PRINT_BUILTIN(OUT, PARAM, ARG, POP) ( \
    PARAM.flag_width && PARAM.flag_precision ? \
    fmt_print_builtin((OUT), PARAM.buffer, va_arg(*(ARG), int), va_arg(*(ARG), int), POP) : \
    PARAM.flag_width || PARAM.flag_precision ? \
    fmt_print_builtin((OUT), PARAM.buffer, va_arg(*(ARG), int), POP) : \
    fmt_print_builtin((OUT), PARAM.buffer, POP) \
)

enum fmt_boolean { FMT_FALSE = 0, FMT_TRUE = 1 };
enum PARAMETER_TYPE { TYPE_INT, TYPE_DOUBLE, TYPE_POINTER, TYPE_PERCENT };
enum PARAMETER_LENGTH { LENGTH_DEFAULT, LENGTH_L, LENGTH_LL, LENGTH_J, LENGTH_Z, LENGTH_T, LENGTH_H, LENGTH_HH, LENGTH_L_UC };

/** Formattable parameter */
struct fmt_param{

    const char *    begin;
    const char *    end;
    char *          id;
    char *          options;
    char            buffer[FMT_MAX_FORMAT_LENGTH + 1];
    unsigned int    flag_width      : 1;
    unsigned int    flag_precision  : 1;
    unsigned int    length          : 4;
    unsigned int    type            : 2;
};

/** Handler */
struct fmt_handler{

    int             hash;
    const char *    id;
    fmt_formatter   formatter;
};


/** Registered handler */
static struct fmt_handler handlers[FMT_MAX_FORMATTERS] = { {0, NULL, NULL} };

/** Initialize stream channeled to a file */
void fmt_stream_file(struct fmt_stream * stream, FILE * file){

    if(stream == NULL) return;

    stream->file    = file;
    stream->buffer  = NULL;
    stream->bytes   = 0;
    stream->written = 0;
}

/** Initialize stream channeled to a string buffer */
void fmt_stream_buffer(struct fmt_stream * stream, char * buffer, size_t bytes){

    if(stream == NULL) return;

    stream->file    = NULL;
    stream->buffer  = buffer;
    stream->bytes   = bytes;
    stream->written = 0;
}

/** Register a new formatter */
int fmt_register_formatter(fmt_formatter formatter, const char * id){

    if(formatter != NULL && id != NULL){

        struct fmt_handler * handler;

        for(handler = handlers; handler < &handlers[FMT_MAX_FORMATTERS]; handler++){
            if(handler->hash == 0){
                handler->hash      = HASH(id);
                handler->id        = id;
                handler->formatter = formatter;
                return(FMT_TRUE);
            }
        }
    }

    return(FMT_FALSE);
}

/** Parse next parameter */
static inline int fmt_next_param(const char * format, struct fmt_param * param){

    for(param->begin = strchr(format, PARAM_MARK); param->begin != NULL; param->begin = strchr(param->begin + 1, PARAM_MARK)){

        if(param->begin[1] == PARAM_BEGIN){
            /* Parse extended parameter */
            size_t length = 0;

            param->end = strchr(param->begin + 2, PARAM_END);

            /* check length */
            length = (param->end != NULL ? param->end - param->begin - 2 : 0);
            if( length > 0 && length < sizeof(param->buffer) ){

                memcpy(param->buffer, param->begin + 2, length);
                param->buffer[length] = '\0';
                param->options = strchr(param->buffer, PARAM_OPTIONS);
                if(param->options != NULL){
                    *param->options = '\0';
                    param->options++;
                }
                param->id = param->buffer;
                return(FMT_TRUE);
            }

        }else{
            /* Parse builtin parameter */
            const char * tmp = param->begin + 1;
            size_t length;

            /* skip flags */
            while(*tmp == '-' || *tmp == '+' || *tmp == ' ' || *tmp == '#' || *tmp == '0'){
                tmp++;
            }
            /* skip minimum field width */
            if(( param->flag_width = (*tmp == '*') )){ tmp++; }else{ SKIP_NUMBERS(tmp); }
            /* skip precision */
            if(*tmp == '.'){
                if(( param->flag_precision = (*++tmp == '*') )){ tmp++; }else{ SKIP_NUMBERS(tmp); }
            }
            /* length modifier */
            switch(*tmp){
                case 'h': tmp++; if(*tmp == 'h'){ tmp++; param->length = LENGTH_HH; }else{ param->length = LENGTH_H; } break;
                case 'l': tmp++; if(*tmp == 'l'){ tmp++; param->length = LENGTH_LL; }else{ param->length = LENGTH_L; } break;
                case 'j': tmp++; param->length = LENGTH_J; break;
                case 'z': tmp++; param->length = LENGTH_Z; break;
                case 't': tmp++; param->length = LENGTH_T; break;
                case 'L': tmp++; param->length = LENGTH_L_UC; break;
                default:         param->length = LENGTH_DEFAULT;
            }
            /* conversion specifier */
            switch(*tmp){
                case 'd': case 'i': case 'u': case 'o': case 'x': case 'X': case 'c':           param->type = TYPE_INT;     break;
                case 'f': case 'F': case 'e': case 'E': case 'g': case 'G': case 'a': case 'A': param->type = TYPE_DOUBLE;  break;
                case 's': case 'p': case 'n':                                                   param->type = TYPE_POINTER; break;
                case '%':                                                                       param->type = TYPE_PERCENT; break;
                default:                                                                        return(FMT_FALSE);
            }
            /* check length */
            length = (tmp - param->begin + 1);
            if( length >= sizeof(param->buffer) ){ return(FMT_FALSE); }
            /* return builtin parameter */
            memcpy(param->buffer, param->begin, length);
            param->buffer[length] = '\0';
            param->end = tmp;
            param->id = NULL;
            return(FMT_TRUE);
        }
    }

    return(FMT_FALSE);
}

/** Print formatted variable list of arguments */
int fmt_vprint(struct fmt_stream * out, const char * format, va_list * arg){

    struct fmt_param param = { NULL, NULL, NULL, NULL, {0}, 0, 0, 0, 0 };
    int written = 0;

    if( format != NULL && IS_READY(out) ){

        int result;

        while( fmt_next_param(format, &param) ){

            if(param.begin > format){

                result = fmt_print_builtin(out, "%.*s", (int)(param.begin - format), format);
                if(result == FMT_ERROR){ return(FMT_ERROR); }else{ written += result; }
            }

            if(param.id == NULL){
                /* print builtin parameter */
                result = FMT_ERROR;

                switch(param.type){
                    case TYPE_INT:
                        switch(param.length){
                            case LENGTH_L:  result = PRINT_BUILTIN(out, param, arg, va_arg(*arg, long int)); break;
                            case LENGTH_LL: result = PRINT_BUILTIN(out, param, arg, va_arg(*arg, LONG_LONG_INT)); break;
                            case LENGTH_J:  result = PRINT_BUILTIN(out, param, arg, va_arg(*arg, intmax_t)); break;
                            case LENGTH_Z:  result = PRINT_BUILTIN(out, param, arg, va_arg(*arg, size_t)); break;
                            case LENGTH_T:  result = PRINT_BUILTIN(out, param, arg, va_arg(*arg, ptrdiff_t)); break;
                            default:        result = PRINT_BUILTIN(out, param, arg, va_arg(*arg, int)); break;
                        }
                        break;
                    case TYPE_DOUBLE:
                        if( param.length == LENGTH_L_UC ){
                            result = PRINT_BUILTIN(out, param, arg, va_arg(*arg, long double));
                        }else{
                            result = PRINT_BUILTIN(out, param, arg, va_arg(*arg, double) );
                        }
                        break;
                    case TYPE_POINTER:      result = PRINT_BUILTIN(out, param, arg, va_arg(*arg, void *) ); break;
                    case TYPE_PERCENT:      result = PRINT_BUILTIN(out, param, arg, 0); break;
                }

            }else if(*param.id == PARAM_META){
                /* print meta formatter */
                const char * meta_format = va_arg(*arg, const char *);
                va_list * meta_arg = va_arg(*arg, va_list *);
                result = fmt_vprint(out, meta_format, meta_arg);

            }else if(*param.id == PARAM_INDIRECT){
                /* print indirect formatter */
                fmt_formatter indirect_formatter = va_arg(*arg, fmt_formatter);
                result = indirect_formatter(out, param.id + 1, param.options, arg);

            }else{
                /* print extended parameter */
                struct fmt_handler * handler = NULL;
                int hash = HASH(param.id);

                /* find registered handler by id */
                for(handler = handlers; handler < &handlers[FMT_MAX_FORMATTERS]; handler++){
                    if(handler->hash == hash && strcmp(handler->id, param.id) == 0){
                        break;
                    }
                }

                if(handler < &handlers[FMT_MAX_FORMATTERS]){
                    result = handler->formatter(out, param.id, param.options, arg);
                }else{
                    (void)fmt_print_builtin(out, "%s@%p", param.id, va_arg(*arg, void *));
                    result = FMT_ERROR;
                }
            }

            if(result == FMT_ERROR){ return(FMT_ERROR); }else{ written += result; }

            format = param.end + 1;
        }

        if(*format != '\0'){

            result = fmt_print_builtin(out, "%s", format);
            if(result == FMT_ERROR){ return(FMT_ERROR); }else{ written += result; }
        }
    }

    return(written);
}

/** Print formatted (builtin parameters only) */
int fmt_print_builtin(struct fmt_stream * out, const char * format, ...){

    int written;
    va_list arg;

    if( !IS_READY(out) ){ return(FMT_ERROR); }

    va_start(arg, format);

    if( IS_FILE(out) ){

        written = vfprintf(out->file, format, arg);

    }else{

        written = vsnprintf(out->buffer, out->bytes, format, arg);

        if(written > 0){
            out->buffer += written;
            out->bytes -= written;
        }
    }

    if(written > 0){ out->written += written; }

    va_end(arg);

    return(written < 0 ? FMT_ERROR : written);
}

/** Print formatted */
int fmt_print(struct fmt_stream * out, const char * format, ...){

    int written;
    va_list arg;

    va_start(arg, format);

    written = fmt_vprint(out, format, &arg);

    va_end(arg);

    return(written);
}

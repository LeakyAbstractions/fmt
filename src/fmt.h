/**
 *
 * @file        fmt.h
 *
 * fmt header file
 *
 * @version     1.3.2
 * @author      Copyright (c) 2017 Guillermo Calvo
 *
 */

# ifndef FMT_H
# define FMT_H

# include <stdio.h>
# include <stdarg.h>

# define FMT_ERROR ( (int)-1 )

/** Output stream */
struct fmt_stream{

    FILE *  file;
    char *  buffer;
    size_t  bytes;
    size_t  written;
};

/** Custom formatter */
typedef int (*fmt_formatter)(struct fmt_stream * out, const char * id, const char * options, va_list * arg);

/** Register a new formatter */
extern int fmt_register_formatter(fmt_formatter formatter, const char * id);

/** Initialize stream channeled to a string buffer */
extern void fmt_stream_buffer(struct fmt_stream * stream, char * buffer, size_t bytes);

/** Initialize stream channeled to a file */
extern void fmt_stream_file(struct fmt_stream * stream, FILE * file);

/** Print formatted */
extern int fmt_print(struct fmt_stream * out, const char * format, ...);

/** Print formatted (builtin parameters only) */
extern int fmt_print_builtin(struct fmt_stream * out, const char * format, ...);

/** Print formatted variable list of arguments */
extern int fmt_vprint(struct fmt_stream * out, const char * format, va_list * arg);

# endif

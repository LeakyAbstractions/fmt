---
title: Functions
sections:
- fmt_register_formatter
- fmt_stream_buffer
- fmt_stream_file
- fmt_print
- fmt_print_builtin
- fmt_vprint
---

## fmt_register_formatter

Register a new formatter.

```c
extern int fmt_register_formatter(fmt_formatter formatter, const char * id);
```


## fmt_stream_buffer

Initialize stream channeled to a string buffer.

```c
extern void fmt_stream_buffer(struct fmt_stream * stream, char * buffer, size_t bytes);
```


## fmt_stream_file

Initialize stream channeled to a file.

```c
extern void fmt_stream_file(struct fmt_stream * stream, FILE * file);
```


## fmt_print

Print formatted.

```c
extern int fmt_print(struct fmt_stream * out, const char * format, ...);
```


## fmt_print_builtin

Print formatted (builtin parameters only).

```c
extern int fmt_print_builtin(struct fmt_stream * out, const char * format, ...);
```


## fmt_vprint

Print formatted variable list of arguments.

```c
extern int fmt_vprint(struct fmt_stream * out, const char * format, va_list * arg);
```

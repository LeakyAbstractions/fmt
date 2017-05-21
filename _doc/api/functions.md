---
title: Functions
sections:
- fmt_register_formatter
- fmt_print
- fmt_print_native
- fmt_vprint
- fmt_vprint_native
---

## fmt_register_formatter

Register a new formatter.

```c
extern int fmt_register_formatter(fmt_formatter formatter, const char * id);
```

## fmt_print

Print formatted.

```c
extern int fmt_print(struct fmt_stream * out, const char * format, ...);
```


## fmt_print_native

Print formatted (native parameters only).

```c
extern int fmt_print_native(struct fmt_stream * out, const char * format, ...);
```


## fmt_vprint

Print formatted variable list arguments.

```c
extern int fmt_vprint(struct fmt_stream * out, const char * format, va_list * arg);
```


## fmt_vprint_native

Print formatted variable list arguments (native parameters only).

```c
extern int fmt_vprint_native(struct fmt_stream * out, const char * format, va_list * arg);
```

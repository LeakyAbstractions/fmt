---
title: Types
sections:
- fmt_stream
- fmt_stream_type
- fmt_formatter
---

## fmt_stream

Output stream.

```c
struct fmt_stream{

	FILE *  file;
	char *  buffer;
	size_t  bytes;
	int     written;
};
```


## fmt_formatter

Custom formatter.

```c
typedef int (*fmt_formatter)(struct fmt_stream * out, const char * id, const char * options, va_list * arg);
```

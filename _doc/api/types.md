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
	char    type;
};
```


## fmt_stream_type

Output stream type:

- `FMT_STREAM_BUFFER`
- `FMT_STREAM_FILE`
- `FMT_STREAM_STDOUT`
- `FMT_STREAM_STDERR`

```c
enum fmt_stream_type { FMT_STREAM_BUFFER, FMT_STREAM_FILE, FMT_STREAM_STDOUT, FMT_STREAM_STDERR };
```


## fmt_formatter

Custom formatter.

```c
typedef int (*fmt_formatter)(struct fmt_stream * out, const char * id, const char * options, va_list * arg);
```

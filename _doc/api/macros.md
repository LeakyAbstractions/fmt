---
title: Macros
---

## FMT_ERROR

```c
# define FMT_ERROR                                      ( (int)-1 )
```


## FMT_STREAM

```c
# define FMT_STREAM(FILE, BUFFER, BYTES, TYPE)          {(FILE), (BUFFER), (BYTES), 0, (TYPE)}
```


## FMT_FILE

```c
# define FMT_FILE(FILE)                                 FMT_STREAM((FILE), NULL, 0, FMT_STREAM_FILE)
```


## FMT_STDOUT

```c
# define FMT_STDOUT                                     FMT_STREAM(NULL, NULL, 0, FMT_STREAM_STDOUT)
```


## FMT_STDERR

```c
# define FMT_STDERR                                     FMT_STREAM(NULL, NULL, 0, FMT_STREAM_STDERR)
```


## FMT_BUFFER

```c
# define FMT_BUFFER(BUFFER, BYTES)                      FMT_STREAM(NULL, (BUFFER), (BYTES), FMT_STREAM_BUFFER)
```

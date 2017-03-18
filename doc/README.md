
# fmt

> Print formatted strings

![](https://github.com/guillermocalvo/fmt/raw/master/doc/logo.png)


## A tiny C string formatting library

Write formatted strings to an output stream.


## API


### Types

- `fmt_formatter`: Represents a function that can be registered as a custom formatter
- `fmt_stream`: Represents an output stream that can be channeled to either a file or a string buffer


### Functions

- `fmt_register_formatter`: Register a new formatter
- `fmt_stream_buffer`: Initialize stream channeled to a string buffer
- `fmt_stream_file`: Initialize stream channeled to a file
- `fmt_print`: Print formatted
- `fmt_print_builtin`: Print formatted (builtin parameters only)
- `fmt_vprint`: Print formatted variable list of arguments


## License

This is free software: you can redistribute it and/or modify it under the terms
of the **GNU Lesser General Public License** as published by the
*Free Software Foundation*, either version 3 of the License, or (at your option)
any later version.

This software is distributed in the hope that it will be useful, but
**WITHOUT ANY WARRANTY**; without even the implied warranty of
**MERCHANTABILITY** or **FITNESS FOR A PARTICULAR PURPOSE**. See the
[GNU Lesser General Public License](http://www.gnu.org/licenses/lgpl.html) for
more details.

You should have received a copy of the GNU Lesser General Public License along
with this software. If not, see <http://www.gnu.org/licenses/>.


# fmt

[![Last release](https://img.shields.io/github/release/LeakyAbstractions/fmt.svg)](https://github.com/LeakyAbstractions/fmt/releases)
[![Build status](https://travis-ci.org/LeakyAbstractions/fmt.svg?branch=master)](https://travis-ci.org/LeakyAbstractions/fmt)
[![Code coverage](https://codecov.io/github/LeakyAbstractions/fmt/coverage.svg?branch=master)](https://codecov.io/github/LeakyAbstractions/fmt?branch=master)
[![Static analysis](https://scan.coverity.com/projects/14163/badge.svg)](https://scan.coverity.com/projects/leakyabstractions-fmt)

> Print formatted strings

![](https://github.com/LeakyAbstractions/fmt/raw/master/doc/logo.png)


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


## Author

Copyright 2017 [Guillermo Calvo](https://github.com/guillermocalvo)

[![](https://resume.guillermo.in/assets/images/thumb.png)](https://guillermo.in/)


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

### Required

- **License and copyright notice**: Include a copy of the license and copyright
notice with the code.
- **Library usage**: The library may be used within a non-open-source
application.
- **Disclose Source**: Source code for this library must be made available when
distributing the software.

### Permitted

- **Commercial Use**: This software and derivatives may be used for commercial
purposes.
- **Modification**: This software may be modified.
- **Distribution**: You may distribute this software.
- **Sublicensing**: You may grant a sublicense to modify and distribute this
software to third parties not included in the license.
- **Patent Grant**: This license provides an express grant of patent rights from
the contributor to the recipient.

### Forbidden

- **Hold Liable**: Software is provided without warranty and the software
author/license owner cannot be held liable for damages.

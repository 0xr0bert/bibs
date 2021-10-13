<!--
BIBS, the belief-induced behaviour simulation
Copyright (C) 2021 Robert Greener

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
-->

# BIBS

BIBS is the *belief-induced behaviour simulation*.

# License

This project is licensed under the GNU Public Licence version 3 (GPLv3).
See LICENSE for the full content of the license.

# Compilation

## Dependencies
In order to compile you must have the following dependencies:

- [Meson](https://mesonbuild.com/)
- [Boost](https://www.boost.org/)
- [Google Test](https://github.com/google/googletest)

As well as a C++ compiler.

## Setup the build directory

For my own compilation, I compiled using clang 12.0.1, and ld.lld 12.0.1.
The project *should* also compile using GCC.

To use clang and lld:

```
CC=clang CC_LD=lld CXX=clang++ CXX_LD=lld meson setup build
```

To use GCC and ld:

```
meson setup build
```

## Compilation!

To compile enter the build directory:

```
cd build
```

Then compile:

```
meson compile
```

In the `build` directory, the executable is located at `exe/bibs-exe`, the library is located at `src/libbibs.so`, and the tests are located at `test/bibs-test`.


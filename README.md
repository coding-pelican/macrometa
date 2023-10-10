# Macrometa: Macro Metaprogramming (MCMT) Library for C

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

## Overview

Macrometa (MCMT) is a powerful macro-based library for C that enables metaprogramming, allowing developers to generate complex code during compile-time using preprocessor macros. It is inspired by the article "C/C++ Preprocessor Metaprogramming" by Saad Ahmad and various C preprocessor tricks, tips, and idioms.

### Key Features

- **Metaprogramming Tools**: MCMT provides a wide range of macros for handling empty arguments, manipulating identifiers, concatenating macros, overloading macros, and more.

- **Based on C11 Standard**: MCMT is based on the C11 standard, ensuring compatibility with modern C compilers.

## Library Sections

The MCMT Library is organized into several sections, each dedicated to specific macro functionalities:

- **mcmt_basic**: Basic macros for handling empty arguments and expansions.
- **mcmt_concat**: Macros for concatenating and manipulating identifiers.
- **mcmt_cat**: Macros for complex identifier concatenation and deferring macro calls.
- **mcmt_impl_overload**: Macros for general macro overloading.
- **mcmt_arg**: Macros for manipulating and counting arguments.
- **mcmt_bit_logic**: Macros for bitwise logic operations.
- **mcmt_logic**: Macros for boolean and logical operations.
- **mcmt_list**: Macros for handling lists and checking for emptiness.
- **mcmt_tuple**: Macros for working with tuples and enclosed expressions.
- **mcmt_for_each**: Macros for iterating through lists and applying operations.
- **mcmt_compare**: Macros for comparing and checking the existence of macro arguments.
- **mcmt_arith**: Macros for basic arithmetic operations.
- **mcmt_range**: Macros for generating ranges of values.

## Getting Started

To use the MCMT Library in your project, include the `mcmt.h` header file and start leveraging the macros provided by the library. Here's a very simple example:

```c
#include "macrometa.h"
#include <stdio.h>

// Define a macro to square a number.
#define SQUARE(x) MUL(x, x)

int main() {
    int result = SQUARE(5); // Expands to 25 at compile-time.
    printf("Square: %d\n", result);
    return 0;
}
```

## License

This library is distributed under the [MIT License](LICENSE).

## Contributing

Contributions to the MCMT Library are welcome! Feel free to open issues or submit pull requests on the [GitHub repository](https://github.com/coding-pelican/macrometa).

## Author

- **Gyeongtae Kim (DevDasae, @coding-pelican)** - [codingpelican@gmail.com](mailto:codingpelican@gmail.com)

For more information and updates, visit the [GitHub repository](https://github.com/coding-pelican/macrometa).

---
*This library is based on the C11 standard.*

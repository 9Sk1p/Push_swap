*This project has been created as part of the 42 curriculum by yhubaren.*

## Description
The goal of this project is to create my own C library, called libft. It contains reimplementations of various standard C library functions, as well as additional utility functions for string, memory, and linked list manipulation. This library will serve as a foundational tool for my future projects in the 42 curriculum.

**Detailed description of the library:**
The libft library is divided into three main parts:
*   **Libc functions:** Custom implementations of standard C functions (e.g., memset, strlen, atoi, calloc) with the ft_ prefix.
*   **Additional functions:** Utility functions not present in libc, useful for string and memory manipulation (e.g., ft_split, ft_itoa, ft_strjoin).
*   **Linked list functions:** A set of functions to create, modify, and iterate through linked lists using a custom t_list structure.

## Instructions
To compile and use the library, run the following commands at the root of the repository:
*   `make` : Compiles the mandatory functions and creates the `libft.a` static library.
*   `make clean` : Removes the generated object (.o) files.
*   `make fclean` : Removes the object files and the `libft.a` library.
*   `make re` : Recompiles the entire project.

To use the library in your code, include `#include "libft.h"` in your C files and compile them with the `libft.a` library.

## Resources
*   **Documentation:** The Linux `man` pages were used to understand the exact behavior of standard libc functions.
*   **Testing:** The Tripouille libftTester was used to verify the functionality and memory safety of the code.
*   **AI Usage:** AI was used exclusively to help generate the text for this README.md file. No AI was used for writing or debugging the actual C code of the project.
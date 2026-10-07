#include <stdio.h>
void hello_from_static_lib() { printf("Hello from Static Lib!\n"); }

/* compiling:
gcc -c static_lib.c -o static_lib.o
ar rcs libstatic.a static_lib.o
gcc hello.c -L. -lstatic -o hello_static
*/

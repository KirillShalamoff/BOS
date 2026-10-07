#include <stdio.h>
void hello_from_dynamic_lib() { printf("Hello from Dynamic Lib!\n"); }

/* compiling:
gcc -c -fPIC dynamic_lib.c -o dynamic_lib.o
gcc -shared dynamic_lib.o -o libdynamic.so
gcc hello.c -L. -ldynamic -o hello_dynamic
LD_LIBRARY_PATH=. ./hello_dynamic
*/
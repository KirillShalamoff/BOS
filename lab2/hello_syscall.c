#include <unistd.h> 


int main() {
    char *text = "Hello, World!\n";

    write(1, text, 14);
    return 0;
}


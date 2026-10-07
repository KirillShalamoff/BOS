#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <limits.h>

#define PAGE_SIZE 4096
#define NUM_COUNT (PAGE_SIZE / sizeof(unsigned int))

int main() {
    unsigned int *buffer = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE,
                                MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (buffer == MAP_FAILED) { perror("mmap"); exit(1); }

    pid_t pid = fork();

    if (pid == 0) { // Процесс ЧИТАТЕЛЬ
        unsigned int expected = 0;
        while (1) {
            for (int i = 0; i < NUM_COUNT; i++) {
                unsigned int val = buffer[i];
                if (val != expected) {
                    printf("[Reader] Error! exprcted %u, writed %u\n", expected, val);
                    expected = val;
                } else {
                    printf("[Reader] Success! expected %u, readedd %u\n", expected, val);
                }
                expected++;
                sleep(1);
            }
        }
    } else { // Процесс ПИСАТЕЛЬ
        unsigned int counter = 0;
        printf("[Writer] Начало записи чисел...\n");
        while (1) {
            for (int i = 0; i < NUM_COUNT; i++) {
                buffer[i] = counter++;
                printf("[WRITER] writed: %u\n",buffer[i]);
                            sleep(1);

            }

        }
    }
    return 0;
}
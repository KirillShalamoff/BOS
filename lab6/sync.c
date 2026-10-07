#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

volatile sig_atomic_t ready = 0;
pid_t other_pid;

void handle_ready(int sig) {
    ready = 1;
}

void handle_exit(int sig) {
    if (sig == SIGINT) {
        const char msg[] = "\nПолучен SIGINT. Завершаю работу...\n";
        write(STDOUT_FILENO, msg, sizeof(msg) - 1);
        if (other_pid > 0) kill(other_pid, SIGTERM);
        exit(0);
    }
    if (sig == SIGTERM) {
        const char msg[] = "Завершение: другой процесс остановлен.\n";
        write(STDOUT_FILENO, msg, sizeof(msg) - 1);
        exit(0);
    }
}

int main() {
    unsigned int *buffer = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    size_t count = 4096 / sizeof(unsigned int);

    struct sigaction sa_ready = { .sa_handler = handle_ready };
    sigaction(SIGUSR1, &sa_ready, NULL);
    sigaction(SIGUSR2, &sa_ready, NULL);
    
    struct sigaction sa_exit = { .sa_handler = handle_exit };
    sigaction(SIGINT, &sa_exit, NULL);
    sigaction(SIGTERM, &sa_exit, NULL);

    pid_t pid = fork();

    if (pid == 0) {
        other_pid = getppid();
        unsigned int expected = 0;
        while (1) {
            while (!ready) pause();
            ready = 0;

            for (size_t i = 0; i < count; i++) {
                if (buffer[i] != expected) {
                    printf("Ошибка! Ожидалось %u, получено %u\n", expected, buffer[i]);
                    expected = buffer[i];
                } else {
                    printf("Совпадение! Ожидалось %u, получено %u\n", expected, buffer[i]);
                }
                expected++;
            }
            kill(other_pid, SIGUSR2);
            sleep(1);
        }
    } else {
        other_pid = pid;
        unsigned int val = 0;
        while (1) {
            for (size_t i = 0; i < count; i++) {
                buffer[i] = val++;
                printf("Записано: %u\n", buffer[i]);
            }
            kill(other_pid, SIGUSR1);
            while (!ready) pause();
            ready = 0;
            sleep(1);
        }
    }

    munmap(buffer, 4096);
    return 0;
}
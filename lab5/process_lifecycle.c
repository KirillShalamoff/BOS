#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int global_var = 10;

int main() {
    int local_var = 20;

    printf("=== До вызова fork() ===\n");
    printf("Глобальная: адрес = %p, значение = %d\n", (void*)&global_var, global_var);
    printf("Локальная : адрес = %p, значение = %d\n", (void*)&local_var, local_var);

    printf("Текущий PID: %d\n\n", getpid());

    pid_t pid = fork();

    if (pid < 0) {
        perror("Ошибка при вызове fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        // --- ДОЧЕРНИЙ ПРОЦЕСС ---
        printf("=== Дочерний процесс ===\n");
        printf("PID: %d, PPID: %d\n", getpid(), getppid());

        printf("[Дочерний] До изменения:\n");
        printf("Глобальная: адрес = %p, значение = %d\n", (void*)&global_var, global_var);
        printf("Локальная : адрес = %p, значение = %d\n", (void*)&local_var, local_var);

        global_var = 100;
        local_var = 200;

        printf("[Дочерний] После изменения:\n");
        printf("Глобальная: адрес = %p, значение = %d\n", (void*)&global_var, global_var);
        printf("Локальная : адрес = %p, значение = %d\n", (void*)&local_var, local_var);

        printf("[Дочерний] Завершаю работу...\n\n");
        exit(5);
    }
    else {
        // --- РОДИТЕЛЬСКИЙ ПРОЦЕСС ---
        sleep(1);

        printf("=== Родительский процесс ===\n");
        printf("[Родитель] Значения переменных:\n");
        printf("Глобальная: адрес = %p, значение = %d\n", (void*)&global_var, global_var);
        printf("Локальная : адрес = %p, значение = %d\n", (void*)&local_var, local_var);

        printf("[Родитель] Засыпаю на 30 секунд. Используйте это время для проверки procfs и ps...\n");
        sleep(30);
        printf("[Родитель] Проснулся. Ожидаю завершения дочернего...\n");

        int status;
        pid_t child_pid = wait(&status);

        if (child_pid == -1) {
            perror("Ошибка wait");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status)) {
            printf("[Родитель] Дочерний процесс (PID %d) завершился нормально. Код возврата: %d\n", child_pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("[Родитель] Дочерний процесс завершился из-за сигнала. Номер сигнала: %d\n", WTERMSIG(status));
        } else {
            printf("[Родитель] Дочерний процесс завершился по неизвестной причине.\n");
        }
    }

    return 0;
}



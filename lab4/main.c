#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int global_init = 100;
int global_uninit;
const int global_const = 200;

int* get_local_address() {
    int local_in_func = 42;
    printf("[П.4] Адрес local_in_func внутри функции: %p\n", (void*)&local_in_func);
    return &local_in_func;
}

void test_environment_vars() {
    printf("\n--- 7-8. Переменные окружения ---\n");
    char *env_val = getenv("MY_LAB_VAR");
    printf("Текущее значение MY_LAB_VAR: %s\n", env_val ? env_val : "(не задана)");

    if (env_val != NULL) {
        setenv("MY_LAB_VAR", "NEW_MODIFIED_VALUE", 1);
        printf("Значение изменено внутри программы.\n");

        printf("Новое значение MY_LAB_VAR: %s\n", getenv("MY_LAB_VAR"));
    }
}

void test_heap() {
    printf("\n--- 5-6. Работа с кучей (Heap) ---\n");
    char *buf1 = (char*)malloc(100);
    strcpy(buf1, "hello world");
    printf("Содержимое buf1: %s (Адрес: %p)\n", buf1, (void*)buf1);

    free(buf1);
    printf("Содержимое buf1 после free: %s\n", buf1);

    char *buf2 = (char*)malloc(100);
    strcpy(buf2, "hello world 2");
    printf("Содержимое buf2: %s (Адрес: %p)\n", buf2, (void*)buf2);


    char *mid = buf2 + 50;
    printf("Попытка освободить память по указателю на середину (Адрес: %p)...\n", (void*)mid);

    free(mid);

    printf("Содержимое buf2 после invalid free: %s\n", buf2);
}

int main() {
    printf("--- 1. Адреса переменных ---\n");
    int local_var = 1;
    static int static_var = 2;
    const int local_const = 3;

    printf("1. Локальная переменная:        %p\n", (void*)&local_var);
    printf("2. Статическая переменная:      %p\n", (void*)&static_var);
    printf("3. Локальная константа:         %p\n", (void*)&local_const);
    printf("4. Глобальная инициализиров.:   %p\n", (void*)&global_init);
    printf("5. Глобальная неинициализиров.: %p\n", (void*)&global_uninit);
    printf("6. Глобальная константа:        %p\n", (void*)&global_const);

    printf("\nPID процесса: %d. Проверьте /proc/%d/maps\n", getpid(), getpid());
    printf("Нажмите Enter, чтобы продолжить...\n");
    getchar();

    printf("\n--- 4. Возврат адреса локальной переменной ---\n");
    int *dangling_ptr = get_local_address();
    printf("Адрес, полученный из функции: %p\n", (void*)dangling_ptr);

    printf("Значение по адресу: %d\n", *dangling_ptr);

    test_environment_vars();

    test_heap();

    return 0;
}


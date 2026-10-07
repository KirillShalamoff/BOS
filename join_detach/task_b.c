#include <stdio.h>
#include <pthread.h>

void *thread_func(void *arg) {
    printf("Дочерний поток возвращает 42\n");
    return (void *)42;
}

int main(void) {
    pthread_t thread;
    void *retval;

    pthread_create(&thread, NULL, thread_func, NULL);

    pthread_join(thread, &retval);

    printf("Основной поток получил число: %ld\n", (long)retval);

    return 0;
}
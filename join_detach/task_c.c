#include <stdio.h>
#include <pthread.h>

void *thread_func(void *arg) {

    return "hello world";
}

int main(void) {
    pthread_t thread;
    void *retval;

    pthread_create(&thread, NULL, thread_func, NULL);

    pthread_join(thread, &retval);

    printf("Основной поток получил строку: %s\n", (char *)retval);

    return 0;
}
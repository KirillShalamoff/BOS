#include <stdio.h>
#include <pthread.h>

void *thread_func(void *arg) {
    printf("Дочерний поток работает\n");
    return NULL;
}

int main(void) {
    pthread_t thread;

    pthread_create(&thread, NULL, thread_func, NULL);

    pthread_join(thread, NULL);

    printf("Основной поток: дочерний поток завершился\n");

    return 0;
}
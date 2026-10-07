#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *thread_func(void *arg) {
    printf("TID: %d\n", gettid());
    return NULL;
}

int main(void) {
    pthread_t thread;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    while (1) {
        if (pthread_create(&thread, &attr, thread_func, NULL) != 0) {
            perror("pthread_create failed");
            break;
        }
    }

    pthread_attr_destroy(&attr);

    return 0;
}
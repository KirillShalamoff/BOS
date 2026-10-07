#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *thread_func(void *arg) {
    pthread_detach(pthread_self());

    printf("TID: %d\n", gettid());
    return NULL;
}

int main(void) {
    pthread_t thread;

    while (1) {
        if (pthread_create(&thread, NULL, thread_func, NULL) != 0) {
            perror("pthread_create failed");
            break;
        }
    }

    return 0;
}
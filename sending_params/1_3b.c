#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    int id;
    char *message;
} thread_data_t;

void *detached_thread_func(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;

    printf("[Detached Thread] Processing data:\n");
    printf("  id      = %d\n", data->id);
    printf("  message = \"%s\"\n", data->message);

    free(data->message);
    free(data);

    printf("[Detached Thread] Cleaned up heap memory and exiting.\n");
    return NULL;
}

int main(void) {
    pthread_t tid;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    thread_data_t *heap_data = (thread_data_t *)malloc(sizeof(thread_data_t));
    if (heap_data == NULL) {
        perror("malloc for struct failed");
        pthread_attr_destroy(&attr);
        return 1;
    }

    const char *text = "Hello Detached World!";
    heap_data->message = (char *)malloc(strlen(text) + 1);
    if (heap_data->message == NULL) {
        perror("malloc for string failed");
        free(heap_data);
        pthread_attr_destroy(&attr);
        return 1;
    }
    strcpy(heap_data->message, text);
    heap_data->id = 100;

    int status = pthread_create(&tid, &attr, detached_thread_func, heap_data);
    if (status != 0) {
        perror("pthread_create failed");
        free(heap_data->message);
        free(heap_data);
        pthread_attr_destroy(&attr);
        return 1;
    }

    pthread_attr_destroy(&attr);

    printf("[Main Thread] Thread started detached. Calling pthread_exit().\n");

    pthread_exit(NULL);
}
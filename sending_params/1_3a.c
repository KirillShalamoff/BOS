#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int id;
    char *message;
} thread_data_t;

void *thread_func(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;

    printf("[Child Thread] Received data:\n");
    printf("  id      = %d\n", data->id);
    printf("  message = \"%s\"\n", data->message);

    return NULL;
}

int main(void) {
    pthread_t tid;

    thread_data_t my_data = {
        .id = 42,
        .message = "Hello from main!"
    };

    int status = pthread_create(&tid, NULL, thread_func, &my_data);
    if (status != 0) {
        perror("pthread_create failed");
        return 1;
    }

    pthread_join(tid, NULL);

    printf("[Main Thread] Child thread has finished. Exiting.\n");
    return 0;
}
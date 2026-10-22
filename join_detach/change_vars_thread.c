#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

int global;

void *mythread(void *arg) {
    int local = 1;
    global++;
    local++;
    printf("\nmythread [%d %d %d %ld]: Hello from mythread!\n\
local:%d\nglobal:%d\n", getpid(), getppid(), gettid(), pthread_self(), local, global);
    sleep(100);
	return NULL;
}

int main() {
	pthread_t tid;
	int err;

    for (int i = 0; i < 5; i++) {
        err = pthread_create(&tid, NULL, mythread, NULL);
        if (err) {
            printf("main: pthread_create() failed: %s\n", strerror(err));
            return -1;
        }
    }


    for (int i = 0; i < 5; i++) {
        pthread_join(tid, NULL);
    }


	if (err) {
	    printf("main: pthread_create() failed: %s\n", strerror(err));
		return -1;
	}
	pthread_join(tid, NULL);
	return 0;
}


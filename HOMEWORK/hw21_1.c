#include <stdio.h>
#include <inttypes.h>
#include <sys/types.h>
#include <pthread.h>

enum {SIZE = 10};

struct thread {
    int32_t x;
    pthread_t last;
};

void * handler(void *ptr) {
    struct thread params = *((struct thread*)(ptr));
    if (params.x > 0) {
        pthread_join(params.last, 0);
    }
    printf("%" PRId32 "\n", params.x);
    fflush(stdout);

    return NULL;
}

int main() {
	struct thread threads[SIZE];
    pthread_t thread = 0;

    for (int32_t i = 0; i != SIZE; ++i) {
    	threads[i].last = thread;
        threads[i].x = i;
        pthread_create(&thread, 0, handler, &threads[i]);
    }
    pthread_join(thread, 0);
}
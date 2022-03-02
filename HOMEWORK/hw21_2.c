#include <stdio.h>
#include <inttypes.h>
#include <sys/types.h>
#include <pthread.h>

void * handler() {
    int32_t x;

    if (scanf("%" SCNd32, &x) == 1) {
        pthread_t thread;
        pthread_create(&thread, 0, handler, 0);
        pthread_join(thread, 0);
        printf("%" PRId32 "\n", x);
        fflush(stdout);
    }

    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, 0, handler, 0);
    pthread_join(thread, 0);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h>
#include <sys/types.h>
int * p;
int32_t N;
pthread_t * ptr;

void *process(void * ptr) {
    int n = *((intptr_t *) ptr);
    int32_t tmp, next;
    while (1) {
        read(p[2 * n], &tmp, sizeof(tmp));
        if (scanf("%" SCNd32, &next) == 1) {
            printf("%d " "%" PRId32 "\n" , n, next);
            fflush(stdout);

            next %= N;

            if (next < 0) {
            	next += N;
            }

            write(p[2 * next + 1], &next, sizeof(next));
            fflush(stdout);

        } else {
            next = (n + 1) % N;
            write(p[2 * next + 1], &next, sizeof(next));
            fflush(stdout);

            break;
        }
    }

    return 0;
}

int main(int argc, char *argv[]) {
    N = strtol(argv[1], NULL, 10);

    pthread_t threads[N];
    int32_t d[2 * N];

    ptr = threads;
    p = d;

    int32_t arr[N];

    for (int32_t i = 0; i != N; ++i) {
        arr[i] = i;
        pipe(&(p[2 * i]));
    }

    pthread_attr_t at;
    pthread_attr_init(&at);
    pthread_attr_setstacksize(&at, sysconf(_SC_THREAD_STACK_MIN));

    for (int32_t i = 0; i != N; ++i) {
        pthread_create(&ptr[i], &at, process, &arr[i]);
    }

    int32_t tmp = 0;
    write(p[1], &tmp, sizeof(tmp));

    for (int32_t i = 0; i != N; ++i) {
        pthread_join(ptr[i], 0);
    }

    for (int32_t i = 0; i != N; ++i) {
        close(p[2 * i]);
        close(p[2 * i + 1]);
    }

    pthread_attr_destroy(&at);
}
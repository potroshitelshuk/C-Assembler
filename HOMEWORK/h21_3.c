#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <sys/types.h>


void * count_sum(void *p) {
    int32_t n;
    int64_t * k = p;
    *k = 0;

    while (scanf("%" SCNd32, &n) != EOF) {
        *k += n;
        sched_yield();
    }

    return NULL;
}

int main(int argc, const char *argv[]) {
    int32_t n = atoi(argv[1]);

    pthread_t threads[n];
    int64_t tmp_sum[n];

    pthread_attr_t at;
    pthread_attr_init(&at);
    pthread_attr_setstacksize(&at, sysconf(_SC_THREAD_STACK_MIN));

    for (int32_t i = 0; i != n; ++i) {
        pthread_create(&threads[i], &at, count_sum, tmp_sum + i);
    }

    pthread_attr_destroy(&at);
    int64_t sum_ = 0;

    for (int32_t i = 0; i != n; ++i) {
        pthread_join(threads[i], 0);
        sum_ += tmp_sum[i];
    }

    printf("%" PRId64 "\n", sum_);
    fflush(stdout);

    return 0;
}
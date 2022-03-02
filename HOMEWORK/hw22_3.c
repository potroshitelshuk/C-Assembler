#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <stdatomic.h>

struct Item {
    struct Item *next;
    long long value;
};

enum {SIZE = 100, CNT = 1000};

struct Item * _Atomic start = 0;

void * fill(void * p) {
    long from = (long)(p);

    for (int x = 0; x != CNT; ++x) {
        struct Item * tmp = malloc(sizeof(struct Item));

        tmp->next = atomic_exchange(&start, tmp);
        tmp->value = from + x;
        sched_yield();
    }

    return NULL;
}

int main(int argc, char const *argv[]) {

    pthread_t threads[SIZE];
    pthread_attr_t at;
    pthread_attr_init(&at);
    pthread_attr_setstacksize(&at, sysconf(_SC_THREAD_STACK_MIN));
    for (int i = 0; i != SIZE; ++i) {
        pthread_create(&threads[i], &at, fill, (void *)((long) i * CNT));
    }
    pthread_attr_destroy(&at);
    for (int i = 0; i != SIZE; ++i) {
        pthread_join(threads[i], 0);
    }

    struct Item * tmp;
    while (start) {
        tmp = start;
        printf("%lld\n", start->value);
        start = start->next;
        free(tmp);
    }
    return 0;
}

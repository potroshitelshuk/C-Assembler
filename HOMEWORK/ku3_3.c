#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <limits.h>

enum {OCT = 16, SIZE = 1048576};

typedef struct long_int {
    uint64_t fst;
    uint64_t scnd;
} long_int;


int comparator(const void *p1, const void *p2) {
    long_int n1 = *(long_int *)p1;
    long_int n2 = *(long_int *)p2;
    return !(n1.fst > n2.fst || (n1.fst >= n2.fst && n1.scnd > n2.scnd));
}

typedef struct array{
    long_int *ptr;
    size_t cap;
    size_t sz;
} array;

void add(array *arr, long_int num) {
    if (arr->sz >= arr->cap) {
        arr->cap *= 2;
        long_int *tmp = realloc(arr->ptr, sizeof(long_int) * arr->cap);
        if (!tmp)
            exit(1);
        arr->ptr = tmp;
    }
    arr->ptr[arr->sz] = num;
    arr->sz += 1;
}



int main(int argc, char const *argv[]) {    
    int cnt = 0, i = 0, j = 0;
    uint8_t octet;
    long_int num;
    array arr;
    num.fst = 0;
    num.scnd = 0;
    arr.cap = SIZE;
    arr.ptr = calloc(arr.cap, sizeof(long_int));
    arr.sz = 0;
    
    while (scanf("%" SCNx8, &octet) != EOF) {
        if (cnt < 8) {
            num.fst += (uint64_t)octet << ((7 - cnt) * 8);
        } else {
            num.scnd += (uint64_t)octet << ((15 - cnt) * 8);
        }
        cnt += 1;
        // printf("%d\n", cnt);
        // printf("%d\n", num.scnd);
        // printf("%d\n", num.fst);
        if (cnt == OCT) {
            add(&arr, num);
            cnt = 0;
            num.scnd = 0;
            num.fst = 0;
            
        }
    }

    qsort(arr.ptr, arr.sz, sizeof(long_int), comparator);

    while (i != arr.sz) {
        j = 0;
        while (j != 8) {
            printf("%02x ", (uint8_t)((arr.ptr[i].fst << 8 * j) >> 7 * 8));
            j += 1;
            // printf("%\n" PRIu64, arr.ptr[i].fst);
        }
        j = 0;
        // printf("%\n" PRIu64, arr.ptr[i].fst);
        
        while (j != 8) {
            printf("%02x ", (uint8_t)((arr.ptr[i].scnd << 8 * j) >> 7 * 8));
            j += 1;
            // printf("%\n" PRIu64, arr.ptr[i].scnd);
        }
        // printf("%\n" PRIu64, arr.ptr[i].scnd);
        printf("\n");
        i += 1;
    }
    free(arr.ptr);
    return 0;
}
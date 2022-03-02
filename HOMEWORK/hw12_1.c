#include <stdio.h>
#include <inttypes.h>
#include <time.h>

int main() {
    time_t mid, current;
    int32_t t_time, secs = 60 * 60 * 24, size = 20;
    while (scanf("%"SCNd32, &t_time) != EOF) {
        time(&current);
        if (__builtin_mul_overflow(t_time, secs, &mid) || __builtin_add_overflow(current, mid, &current)) {
            printf("OVERFLOW\n");
        } else {
            char arr[size];
            struct tm *l_t = localtime(&current);
            strftime(arr, size, "%F", l_t);
            printf("%s\n", arr);
        }
    }
    return 0;
}

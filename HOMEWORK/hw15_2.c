#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <inttypes.h>


int main(void) {
    for (int id = 0; id != 3; ++id) {
        if (!fork()) {
            char num[8];
            read(0, num, sizeof(num));
            long n = strtol(num, NULL, 10);
            printf("%d %ld" "\n", id + 1, n * n);
            exit(0);
        }
    }
    // printf("WAT");
    for (int i = 0; i < 3; ++i)
        wait(0);
}


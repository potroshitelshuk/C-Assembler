#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <inttypes.h>


int main(void) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i != n; ++i) {
        pid_t p = fork();
        if (!p) {
            printf("%d ", i);
            exit(0);
        }
        wait(NULL);
    }
    pid_t p = fork();
    if (!p) {
            printf("%d\n", n);
            exit(0);
        }
        wait(NULL);
}


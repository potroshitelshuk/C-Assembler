#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>



void child() {
    pid_t p = fork();
    if (p == 0) {
        printf("3 ");
        exit(0);
    }
    wait(0);
    printf("2 ");
    exit(0);
}

int main(void) {
    pid_t p = fork();
    if (p == 0)
        child();
    wait(0);
    printf("1\n");
    return 0;
}
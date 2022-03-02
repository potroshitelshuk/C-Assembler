#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(void) {
    // struct rlimit lim;
    // lim.rlim_max = 3;
    // setrlimit(RLIMIT_NPROC, &lim);    
    
    int n;
    pid_t id = getpid();
    
    while (scanf("%d", &n) != EOF) {
        pid_t p = fork();
        if (p < 0)
            exit(1);

        if (p) {
            int st;
            waitpid(p, &st, 0);
            if (st == 0) {
                printf("%d\n", n);
                fflush(stdout);
                exit(0);
            }
            if (getpid() == id) {
                printf("-1");
                fflush(stdout);
                exit(0);
            }
            exit(1);
        }
    }
    return 0;
}


#include <signal.h>
#include <stdio.h>
#include <unistd.h>

volatile int case_ = 0;

void signal_handler(int signal)
{
    if (signal == SIGUSR1) {
    	case_ = 0;
    } else {
        if (signal == SIGUSR2)
            case_ = 1;
    }
    
}


int main() {
    

    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sa.sa_flags = SA_RESTART;

    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    printf("%d\n", getpid());
    fflush(stdout);

    int x;
    while(scanf("%d", &x) == 1) {
        if (case_ == 1)
            printf("%d\n", x * x);
        else
            printf("%d\n", -x);
        fflush(stdout);
        // if (cnt >= MAXNUM) {
        //     sigaction(SIGINT, &old_sa, NULL);
        //     break;
        // }
    }
}
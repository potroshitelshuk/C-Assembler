#include <signal.h>
#include <stdio.h>
#include <unistd.h>

volatile sig_atomic_t cnt1 = 0, cnt2 = 0;
volatile int fl = 0;
void signal_handler(int signal)
{
	if (signal == SIGUSR1) {
		printf("%d %d\n", cnt1, cnt2);
        fflush(stdout);
		cnt1 += 1;
	}

	if (signal == SIGUSR2)
		cnt2 += 1;
    if (signal == SIGTERM)
    	fl = 1;
}


int main() {
    sigset_t new, old;
    sigemptyset(&new);
    sigaddset(&new, SIGUSR1);
    sigaddset(&new, SIGUSR2);
    sigaddset(&new, SIGTERM);
    sigprocmask(SIG_BLOCK, &new, &old);


    struct sigaction sa, old_sa;
    sa.sa_handler = signal_handler;
    sa.sa_flags = SA_RESTART;

    sigaction(SIGUSR1, &sa, &old_sa);
    sigaction(SIGUSR2, &sa, &old_sa);
    sigaction(SIGTERM, &sa, &old_sa);
    printf("%d\n", getpid());
    fflush(stdout);

    while(1) {
        sigsuspend(&old);
        if (fl)
        	_exit(0);
    }
    sigprocmask(SIG_UNBLOCK, &new, &old);
    return 0;
}
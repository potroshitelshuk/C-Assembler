#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/signalfd.h>

enum {TIME = 100000, SIZE = 8};

volatile uint32_t last_num = 0, total = 0;

int check_num(uint32_t x) {
    if (x < 2) {
        return 0;
    }
    if (x % 2 == 0)
        return 0;
    for (uint32_t i = 3; i * i <= x; i += 2) {
        if (!(x % i)) {
            return 0;
        }
    }
    return 1;
}


void handler(int signal) {
	if (signal == SIGVTALRM) {
		total += 1;
		printf("%" PRIu32 "\n", last_num);
	    fflush(stdout);
	    if (total == SIZE)
	        exit(0);
	}
    
}


int main() {
    uint32_t from;
    uint32_t to;

    scanf("%" SCNu32 "%" SCNu32, &from, &to);

    struct sigaction action = {};
    action.sa_handler = handler;
    action.sa_flags = SA_RESTART;

    sigemptyset(&action.sa_mask);
    sigaction(SIGVTALRM, &action, NULL);

    struct itimerval timer = {};
    timer.it_value.tv_sec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_value.tv_usec = TIME;
    timer.it_interval.tv_usec = TIME;
    setitimer(ITIMER_VIRTUAL, &timer, NULL);

    uint32_t x = from;
    while (x != to) {
    	if (check_num(x)) {
    		last_num = x;
    	}
    	x += 1;
    }

    if (total != SIZE) {
        printf("-1\n");
        fflush(stdout);
    }
}
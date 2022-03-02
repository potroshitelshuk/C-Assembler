// Сделано на семинаре
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>
#include <sys/signalfd.h>

int main() {
    long long sec;
    int nanosec;
    if (scanf("%lld %d", &sec, &nanosec) != 2) {
        fprintf(stderr, "error in reading values\n");
        exit(1);
    }
    if (0 >= nanosec || nanosec >= 1000000000) {
        fprintf(stderr, "error in nanosecond value %d\n", nanosec);
        exit(1);
    }
    if ((time_t) sec != sec) {
        fprintf(stderr, "error in second value %lld\n", sec);
        exit(1);
    }

    sigset_t s1;
    sigemptyset(&s1);
    sigaddset(&s1, SIGALRM);
    sigprocmask(SIG_BLOCK, &s1, NULL);
    int sfd = signalfd(-1, &s1, 0);

    struct timeval now;
    gettimeofday(&now, NULL);

    sec *= 1000ll;
    sec += nanosec / 1000000;

    long long now_ms = now.tv_sec * 1000ll + now.tv_usec / 1000;

    if (sec <= now_ms) {
        return 0;
    }
    sec -= now_ms;

    struct itimerval itimer = {};
    itimer.it_value.tv_sec = sec / 1000;
    itimer.it_value.tv_usec = (sec % 1000) * 1000ll;
    setitimer(ITIMER_REAL, &itimer, NULL);

    struct signalfd_siginfo info;
    if (read(sfd, &info, sizeof(info)) != sizeof(info)) {
        fprintf(stderr, "error in reading\n");
        exit(1);
    }
    return 0;
}

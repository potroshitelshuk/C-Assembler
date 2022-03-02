#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
// #include <limits.h>
// #include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

int mysys(const char *str) {
    pid_t p = fork();
    if (p < 0)  // если не удалось создать процесс
        return -1;
    if (p) {
        int st;
        waitpid(p, &st, 0);
        return WIFSIGNALED(st) ? WTERMSIG(st) + 128 : WEXITSTATUS(st);
    } else {
        execlp("/bin/sh", "sh", "-c", str, NULL);
        _exit(127);
    }
}
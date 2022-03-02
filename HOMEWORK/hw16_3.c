#include <unistd.h>
#include <sys/wait.h>

int check(char *argv[], int k) {
    if (!fork()) {
        execlp(argv[k], argv[k], NULL);
        _exit(0);
    } else {
        int st;
        wait(&st);
        return (WIFEXITED(st) && !WEXITSTATUS(st)) ? 1 : 0;
    }
}

int main(int argc, char *argv[]) {
    if (check(argv, 1) || check(argv, 2)) {
        int res3 = check(argv, 3);
        return !res3;
    } else {
        return 1;
    }
}
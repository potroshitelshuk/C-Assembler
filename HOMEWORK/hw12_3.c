#include <time.h>
#include <stdio.h>
#include <stdlib.h>

struct tm fill(struct tm tm_new, int y, int mnth, int d, int hrs, int mnt, int sec) {
    tm_new.tm_mon = mnth - 1;
    tm_new.tm_year = y - 1900;
    tm_new.tm_isdst = -1;
    tm_new.tm_sec = sec;
    tm_new.tm_min = mnt;
    tm_new.tm_hour = hrs;
    tm_new.tm_mday = d;
    return tm_new;
}

int main(int argc, char* argv[]) {
    FILE *f = fopen(argv[1], "r");
    time_t st = 0;
    int y, mnth, d, hrs, mnt, sec;
    struct tm tm_new;
    while (fscanf(f, " %d/%d/%d %d:%d:%d ", &y, &mnth, &d, &hrs, &mnt, &sec) != EOF) {
        tm_new = fill(tm_new, y, mnth, d, hrs, mnt, sec);
        time_t fin = mktime(&tm_new);
        if (st != 0) 
            printf("%ld\n", fin - st);
        st = fin;
    }
    fclose(f);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, const char *argv[]) {
    long long cnt = 0;
    struct stat st;
    for (int i = 1; i != argc; ++i) {
        if (lstat(argv[i], &st) == -1) {
            continue;
        }
        if ((S_ISREG(st.st_mode)) && !(S_ISLNK(st.st_mode)) &&
         st.st_nlink == 1 && access(argv[i], F_OK) == 0) {
            cnt += st.st_size;
        } 
    }
    printf("%llu\n", cnt);
}

#include <stdio.h>
// #include <dlfcn.h>
// #include <dirent.h>
// #include <limits.h>
// #include <unistd.h>
// #include <ctype.h>

int main(int argc, char const *argv[]) {
    long long sz = 0;
    long long left, right;
    while (scanf("%llx-%llx", &left, &right) != EOF) {
        scanf("%*[^\n]%*c");
        sz += right - left;
    }
    printf("%lld", sz);
    return 0;
}

#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
// #include <dirent.h>
// #include <limits.h>
// #include <unistd.h>
// #include <ctype.h>

int main(int argc, const char *argv[]) {
    double total;
    void *handle = dlopen("/lib/libm.so.6", RTLD_LAZY);
    if (handle == NULL) {
        fputs(dlerror(), stderr);
        exit(1);
    }
    void *func = dlsym(handle, argv[1]);
    if (func == NULL) {
        printf("%s\n", dlerror());
        exit(1);
    }
    while (scanf("%lf", &total) != EOF) {
        printf("%.10g\n", ((double(*)(double)) func)(total));
    }
}
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main(int argc, char ** argv) {
    int x = 1;
    int64_t total = 0;
    while (x != argc) {
        
        int descr = open(argv[x], O_RDWR);
        if (descr == -1) {
            printf("-1\n");
            x += 1;
            continue;
        }

        struct stat s;

        if (fstat(descr, &s) == -1) {
            close(descr);
            printf("-1\n");
            x += 1;
            continue;
        }

        if (!s.st_size) {
            printf("0\n");
            x += 1;
            continue;
        }

        void *m = mmap(NULL, s.st_size, PROT_READ, MAP_SHARED, descr, 0);

        if (m == MAP_FAILED) {
            printf("-1\n");
            close(descr);
            x += 1;
            continue;
        }
        total = 0;
        char *m1 = (char*)(m);
        for (long i = 0; i != s.st_size; ++i)
            if (m1[i] == '\n')
                ++total;

        if (m1[s.st_size - 1] != '\n')
            ++total;

        printf("%lld\n", total);
        close(descr);
        munmap(m, s.st_size);
        x += 1;
    }
}

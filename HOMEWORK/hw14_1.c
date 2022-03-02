#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
// #include <ctype.h>
// #include <inttypes.h>


int main(int argc, const char *argv[]) {
    double total = 0;
    size_t x = 0;
    if (argc != 2)
        exit(1);
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        exit(1);
    off_t l = lseek(fd, 0, SEEK_END);
    if (l == -1) {
        close(fd);
        exit(1);
    }
    double *m = (double*)(mmap(NULL , l, PROT_READ, MAP_PRIVATE, fd, 0));
    size_t len = l / sizeof(double);
    while (x != len) {
        total += m[x];
        x += 1;
    }
    total /= len;
    printf("%a\n", total);
    munmap(m, l);
    close(fd);
    return 0;
}
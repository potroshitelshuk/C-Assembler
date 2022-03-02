#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[]) {
    int descr = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0600);
    unsigned short x;
    while (scanf("%hu", &x) != EOF) {
        unsigned char mas[2];
        mas[1] = x;
        x >>= 8;
        mas[0] = x;
        // size_t p = write(descr, mas, 2);
        write(descr, mas, 2);
    }
    close(descr);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <fcntl.h>

int main(int argc, char const *argv[]) {
    int file = open(argv[1], O_RDONLY), is_any_x = 0;
    uint16_t x, temp, maximum = 0;
    while(1) {
        int n_bytes = read(file, &temp, 1);
        if (n_bytes == 0) { // if EOF
            break;
        }
        x = (temp << 8u);
        read(file, &temp, 1);
        x += temp;
        if ((x % 3 == 0) && (x > maximum)) {
            maximum = x;
            is_any_x = 1;
        }
    }
    if (is_any_x == 1)
        printf("%" PRIu16 "\n", maximum);
}
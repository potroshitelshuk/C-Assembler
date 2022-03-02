#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include <fcntl.h>
#include <sys/mman.h>


int main(int argc, char ** argv) {
    int r = atoi(argv[2]);
    int c = atoi(argv[3]);
    int64_t len = r * c * sizeof(int32_t);
    int descr = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
    ftruncate(descr, len);
    int32_t * table = mmap(NULL, len, PROT_WRITE, MAP_SHARED, descr, 0);

    int32_t i = 1, min_c = 0, min_r = 0, max_c = c, max_r = r;
    while (min_c < max_c && min_r < max_r) {
        for (int32_t h = min_c; h != max_c; ++h)
            table[h + min_r * c] = i++;

        if (++min_r >= max_r)
            break;

        for (int32_t v = min_r; v != max_r; ++v)
            table[(max_c - 1) + v * c] = i++;

        if (--max_c <= min_c)
            break;

        for (int32_t h = max_c; h > min_c; --h)
            table[h + (max_r - 1) * c - 1] = i++;

        if (--max_r <= min_r)
            break;

        for (int32_t v = max_r - 1; v > min_r - 1; --v)
            table[v * c + min_c] = i++;

        ++min_c;
    }

    munmap(table, len);
    close(descr);
}

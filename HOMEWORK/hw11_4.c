#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


struct Node {
    int32_t key;
    int32_t left_idx;
    int32_t right_idx;
};

int file_d;
void incorrect(int code) {
    exit(code);
}

void process(int32_t st, int code) { // descending print
    struct Node head;
    lseek(file_d, sizeof(head) * st, SEEK_SET);
    if (read(file_d, &head, sizeof(struct Node)) < sizeof(struct Node))
        incorrect(code);
    if (head.right_idx) {
        process(head.right_idx, code);
    }
    printf("%" PRId32 "\n", head.key);
    if (head.left_idx) {
        process(head.left_idx, code);
    }
}

int main(int argc, char **argv) {
    int start = 0, code = 0; // start from index = 0
    file_d = open(argv[1], O_RDONLY);
    process(start, code);
    close(file_d);
}
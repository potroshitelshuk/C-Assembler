#include<stdio.h>
#include<stdint.h>
#include<inttypes.h>
int main(int argc, char *argv[]) {
    uint32_t x, y;
    int flag = scanf("%" PRIu32 "%" PRIu32, &x, &y);
    if (flag != 2) {
        return 1;
    }
    printf("%" PRIu32 "\n", (x / 2) + (y / 2) + (x & y & 1));
    return 0;
}
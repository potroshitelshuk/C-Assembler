#include<stdio.h>
#include<stdint.h>
#include<inttypes.h>
#include<stdlib.h>

enum {BLOCK = 17, OCT = 8};
int main(int argc, char *argv[]) {
	int ind1 = 0, ind2 = 0, fl = 0;
	uint32_t x, res = 0;
	while (scanf("%" SCNx32, &x) == 1) {
		ind1 += 1;
		if (ind1 % BLOCK == 0) {
			ind1 = 0;
			res <<= OCT;
			res += x;
			fl = 1;
		}
		else {
			if (fl == 0) {
				res <<= OCT;
				res += x;
			} else {
				fl = 0;
			}
		}
		if ((ind2 % 4 == 0) && (ind2 != 0)) {
			printf("%" PRIu32 "\n", res);
			res = 0;
			ind2 = 0;
		}
		ind2 += 1;
		if (fl == 1)
			ind2 = 0;
	}
	return 0;
}
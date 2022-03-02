#include<stdio.h>
#include<inttypes.h>

int is_ok(uint32_t x) {
	if (x == 0)
		return 1;
	while (!(x & 1))
		x = x >> 1;
	return x <= 0xffffff;
};

int main(int argc, char *argv[]) {
	uint32_t x;
	while (scanf("%" SCNu32, &x) == 1)
		printf("%d\n", is_ok(x));
	return 0;
}
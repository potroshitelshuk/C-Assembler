#include<stdio.h>
#include<inttypes.h>
#include<stdint.h>

int check(uint64_t dec, uint64_t last_bit, int n) {
	if (dec > (1u << (n - 1)) || (dec == (1u << (n - 1)) && last_bit))
		return 1;
	return 0;
}

uint32_t fixed_mul(uint32_t a, uint32_t b, int n) {
	uint32_t max_num = UINT32_MAX;
	uint64_t res = (uint64_t)a * b;
	if (n != 0) {
		uint64_t mask = ((uint64_t)1u << n) - 1;
		uint64_t dec = res & mask;
		res >>= n;
		uint64_t last_bit = (res & 1u);
		res += check(dec, last_bit, n);
	}
	if (res > max_num)
		return max_num;
	return res;
};
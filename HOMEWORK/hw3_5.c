#include <stdio.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

int check(__uint128_t prelast_bit, __uint128_t dec) {
 	if (dec > 5 * 1e7) {
 		return 1;
 	} else {
 		if (dec < 5 * 1e7) {
 			return 0;
 		} else {
 			if (prelast_bit % 2 == 0)
		 		return 0;
		 	if (prelast_bit % 2 == 1)
		 		return 1;
 		}
 	}
 	return 0;
}


int nulls(__uint128_t x) {
	int c = 10;
	for (int i = 1; i != 9; ++i) {
		if (x == 0)
			return 1;
		if (x / c == 0)
			return i;
		c *= 10;
	}
	return 8;
}

int main() {
	char s[200];
	int c, i = 0, fl1 = 0, fl2 = 0, sign1 = 1, sign2 = 1, count1 = 0, count2 = 0, count_f1 = 0, count_f2 = 0;
	long long x1 = 0, x2;
	__uint128_t val1 = 0, val2;
	while ((c = getchar_unlocked()) != EOF) {
		if (c == '\n') {
			s[i] = '\0';
			const char *str = s;
			char *eptr;
			x2 = strtoll(str, &eptr, 10);
			if (x2 < 0) {
				x2 *= -1;
				sign2 = -1;
			}
			int count_dec1 = count1 - count_f1;
			int count_dec2 = count2 - count_f2;
			if (x2 != 0 && count_dec1 < 9 && count_dec2 < 9 && count_f1 < 11 && count_f2 < 11) {
				val2 = (__uint128_t)x2;
				val1 *= pow(10, (8 - count_dec1));
				val2 *= pow(10, (8 - count_dec2));
				val1 *= 1e10;
				__uint128_t res = val1 / val2;
				__uint128_t prelast_bit = (res / 1e8);
				prelast_bit %= 10;
				__uint128_t last_bit = (res / 1e7);
				__uint128_t dec = res % 100000000;
				last_bit %= 10;
				res /= 1e2;
				res += check(prelast_bit, dec);
				uint64_t fst = (uint64_t)res / 1e8;
				uint64_t snd = (uint64_t)res % 100000000;
				int nulls_cnt = 8 - nulls(snd);
				if (sign1 * sign2 == -1 && (fst != 0 || snd != 0))
					printf("-");	
				printf("%" PRIu64 ".", fst);
				for (int j = 0; j != nulls_cnt; ++j)
					printf("0");
				printf("%" PRIu64 "\n", snd);
			} else {
				printf("%s\n", "ERROR");
			}
			count1 = 0;
			count2 = 0;
			count_f1 = 0;
			count_f2 = 0;
			sign1 = 1;
			sign2 = 1;
			fl1 = 0;
			fl2 = 0;
			i = 0;
		} else {
			if (c == ' ') {
				fl1 = 1;
				fl2 = 0;
				s[i] = '\0';
				const char *str = s;
	            char *eptr;
	            x1 = strtoll(str, &eptr, 10);
	            if (x1 < 0) {
					x1 *= -1;
					sign1 = -1;
				}
				val1 = (__uint128_t)x1;
	            i = 0;
			} else {
				if (c != '.') {
					s[i] = c;
					i++;
					if (!fl1) {
						count1 += 1;
						if (!fl2)
							count_f1 += 1;
					} else {
						count2 += 1;
						if (!fl2)
							count_f2 += 1;
					}
				} else {
					fl2 = 1;
				}
			}
		}
	}
}
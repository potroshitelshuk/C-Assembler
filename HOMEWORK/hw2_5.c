#include<stdio.h>
#include<inttypes.h>

int imull_overflow(int64_t a, int64_t b, int64_t *res) {
	*res = (int64_t)((uint64_t)(a) * (uint64_t)(b));

	if (a > 0 && b > 0 && a > (INT64_MAX / b)) {
		return 1;
	}
	if (a < 0 && b < 0) {
		if ((a == -1 && b == INT64_MIN) || (a == INT64_MIN && b == -1)) {
			return 1;
		} else { 
			if (a == -1 || b == -1) {
				return 0;
			} else {
				if (a < INT64_MAX / b) 
					return 1;
			}
		}
	}
	if (a > 0 && b < 0 && (b < INT64_MIN / a)) {
		return 1;
	}
	if (a < 0 && b > 0 && a < (INT64_MIN / b)) {
		return 1;
	}
	return 0;
};
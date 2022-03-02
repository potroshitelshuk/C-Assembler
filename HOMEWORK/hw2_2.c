#include<stdio.h>
#include<stdint.h>
#include<ctype.h>
#include<inttypes.h>
#include<stdlib.h>

int32_t satsum(int32_t v1, int32_t v2) {
	int32_t c;
	// Переполнения нет
	if (!__builtin_add_overflow(v1, v2, &c)) {
		return c;
	}
	// v1 < 0, v2 > 0 - переполнения не будет
	// Переполнени есть
	if (v1 < 0) {
		return (int32_t) (1u << 31);
	} else {
		return (int32_t) ((1u << 31) - 1);
	}
};

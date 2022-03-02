#include<stdio.h>
#include<stdint.h>
#include<ctype.h>
#include<inttypes.h>
#include<stdlib.h>
uint32_t satsum(uint32_t v1, uint32_t v2) {
	uint32_t c;
	// Переполнения нет
	if (!__builtin_add_overflow(v1, v2, &c)) {
		return c;
	}
	// Переполнени есть
	return (uint32_t) (((1u << 31) - 1) * 2) + 1;
};
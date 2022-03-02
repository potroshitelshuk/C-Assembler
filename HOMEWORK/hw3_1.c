#include<stdio.h>

union U_u {
	float f;
	struct {
		unsigned m:23; // Мантисса
		unsigned p:8;  // Целая часть
		unsigned s:1;  // Знак
	};
};

int main(int argc, char *argv[]) {
	float x;
	while (scanf("%f", &x) == 1) {
		union U_u u;
		u.f = x;
		printf("%u %u %x\n", u.s, u.p, u.m);
	}
	return 0;
}
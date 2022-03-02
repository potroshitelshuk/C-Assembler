#include<stdio.h>
#include<stdint.h>
#include<ctype.h>
#include<stdlib.h>
enum {BASE = 7};
int main(int argc, char *argv[]) {
	int count = 0;
	int fl = 0, add = 0, count_pr = 0, count_dot = 0;
	double num = 0, pw = 1.0 / BASE, fract = 0;
	int c;
	while ((c = getchar_unlocked()) != EOF) {
		if (-1 < (c - '0') && (c - '0') < 8) {
			add = 1;
			count = 0;
		}
		if (count > 1)
			fl = 0;
		if (isspace(c)) { // Если это пробел...
			count_dot = 0;
			count += 1;
			if (count > 1)
				continue;
			fl = 2;
		}
		if (fl == 1) {
			fract += pw * (c - '0');
			pw /= BASE;
		}
		if (c == '.') {
			if (count_dot == 0) {
				fl = 1;
				count_dot += 1;
			} else {
				return 0;
			}
		}
		if (fl == 0) {
			num = num * BASE + (c - '0');
		}
		if ((fl == 2 && count == 1) || c == EOF) {
			num += fract;
			if (add == 1) {
				printf("%.10g\n", num);
				count_pr += 1;
			}
			pw = 1.0 / BASE;
			fl = 0;
			fract = 0;
			num = 0;
		}
	}
	if (count_pr == 0 && add) {
		num += fract;
		printf("%.10g\n", num);
	}
	return 0;
}
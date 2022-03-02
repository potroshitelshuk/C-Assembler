#include <stdio.h>

int mystrcmp(const char *str1, const char *str2) {
	while (*str1 || *str2) {
		if ((unsigned char)*str1 > (unsigned char)*str2) {
			return 1;
		}
		if ((unsigned char)*str1 < (unsigned char)*str2) {
			return -1;
		}
		str1 += 1;
		str2 += 1;
	}

	return 0;
}

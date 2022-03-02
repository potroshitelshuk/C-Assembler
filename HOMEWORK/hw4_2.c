#include <stdio.h>
#include <string.h>

void normalize_path(char *buf) {
	char *str = buf;
	int count = 0;
	while (*str) {
		if (*str != '/') {
			*buf = *str;
			++buf;
			count = 0;
		}

		if (*str == '/' && count == 0) {
			*buf = '/';
			++buf;
			count++;
		}
		++str;
	}
	*buf = '\0';
}
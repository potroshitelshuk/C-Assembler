#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>

enum {BASE = 10, INT8T = 1, INT16T = 2, INT32T = 4, ERR = -1};

int main(int argc, char *argv[]) {
	for (int i = 1; i != argc; ++i) {
		const char *str = argv[i];
		int ans = ERR;
		char *eptr;
		errno = 0;
		long x = strtol(str, &eptr, BASE);
		if (*str && !*eptr && !errno) {
			if ((int8_t)(x) == x)  {
				ans = INT8T;
			} else if ((int16_t)(x) == x) {
				ans = INT16T;
			} else if ((int32_t)(x) == x) {
				ans = INT32T;
			} 			
		}
		printf("%d\n", ans);
	}
	return 0;
}
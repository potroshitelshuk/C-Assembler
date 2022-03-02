#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
enum {SIZE = 6};

typedef double (* funcptr_t) (double);
struct FunctionTable {
	const char *key;
	funcptr_t func;
};

static const struct FunctionTable arr[] = {
	{"cos", cos},
	{"sin", sin},
	{"exp", exp},
	{"sqrt", sqrt},
	{"tan", tan},
	{"log", log}
};

int main() {
	double x;
	int fl = 0;
	char *str = NULL;
	while (scanf("%ms%lf", &str, &x) == 2) {
		double ans;
		for (int i = 0; i < SIZE; ++i)
			if (strcmp(arr[i].key, str) == 0) {
				ans = arr[i].func(x);
				fl = 1;
				break;
			}
		if (!fl)
			ans = NAN;
		printf("%a\n", ans);
		free(str);
		str = NULL;
		fl = 0;
	}
	return 0;
}

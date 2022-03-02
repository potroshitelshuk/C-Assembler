#include<stdio.h>
#include<stdint.h>
#include<inttypes.h>
int main(int argc, char *argv[]) {
	long long a, b;
	int n;
	int flag = scanf("%lld %lld %d", &a, &b, &n);
    if (flag != 3) {
        return 1;
    }
	printf("%*s", n, "");
	for (long long i = a; i != b; ++i)
		printf(" %*lld", n, i);
	printf("\n");
	for (long long i = a; i != b; ++i) {
		printf("%*lld", n, i);
		for (long long j = a; j != b; ++j)
			printf(" %*lld", n, i * j);
		printf("\n");
	}

	return 0;
}
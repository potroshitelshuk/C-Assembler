#include<stdio.h>
#include<stdint.h>
#include<ctype.h>
int main(int argc, char *argv[]) {
	int c, sum = 0;
	while ((c = getchar_unlocked()) != EOF) {
		if (isdigit(c))
			sum += (c - '0');
	}
	printf("%d\n", sum);
	return 0;
}

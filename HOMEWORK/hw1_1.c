#include<stdio.h>
int main(int argc, char *argv[]) {
	int x, y;
	int scanned = scanf("%d %d", &x, &y);
    if (scanned != 2) {
        return 1;
    }
	printf("%d\n", x + y);
	return 0;
}

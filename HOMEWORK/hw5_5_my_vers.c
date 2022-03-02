#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int c, cnt = 0, length = 0;
	char *arr;
	int i = 0;
	while ((c = getc(stdin)) != EOF) {
		arr[i] = c;
		i++;
		cnt += 1;
	}
	arr[i] = '\0';
	for (size_t j = 0; j < cnt;) {
        char ch = (int)arr[j];
        if (0xf0 == (0xf8 & ch)) {
            j += 4;
        } else if (0xe0 == (0xf0 & ch)) {
            j += 3;
        } else if (0xc0 == (0xe0 & ch)) {
            j += 2;
        } else {
            j += 1;
        }
        length++;
    }
	printf("Length: %d\nArr: %s", length, arr);
	return 0;
}
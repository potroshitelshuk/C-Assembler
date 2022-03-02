#include <stdio.h>
#include <stdlib.h>

char *ptr;
size_t sz = 0, mx = 2, temp = 0;
int c, fl = 0;

void check_first() {
	if (c == EOF) {
		free(ptr);
		fl = 1;
	} else {
		if (c == '\n') {
			ptr[sz] = c;
			ptr[sz + 1] = '\0';
			sz = 0;
			fl = 2;
		} else {
			ptr[sz] = c;
			sz += 1;
		}
	}
}

void check_size() {
	if (mx == sz) {
		temp = mx*2;
		char *ptr_new = realloc(ptr, temp*sizeof(char));
		mx = temp;
		if (ptr_new) {
			ptr = ptr_new;
		} else {
			free(ptr);
			fl = 1;
		}
	}
}

char *getline2(FILE *f) {
	ptr = malloc(mx*sizeof(*ptr));
	if (!ptr) {
		return NULL;
	} else {
		c = getc(f);
		check_first();
		if (fl == 1) {
			return NULL;
		} else {
			if (fl == 2) {
				return ptr;
			}
		}
	}
	while ((c = getc(f)) != EOF) {
		if (mx == sz) {
			temp = mx*2;
			char *ptr_new = realloc(ptr, temp*sizeof(char));
			mx = temp;
			if (ptr_new) {
				ptr = ptr_new;	
			} else {
				free(ptr);
				return NULL;
			}
		}
		ptr[sz] = c;
		sz += 1;
		if (c == '\n')
			break;
	}
	
	check_size();

	if (fl)
		return NULL;
	ptr[sz] = '\0';
	sz = 0;
	return ptr;
}

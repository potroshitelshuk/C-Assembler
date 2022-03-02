#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


int comp(const void *ptr1, const void *ptr2, void* res) { 
	const int *data = (const int*) res;
	int ind1 = *(const int*) ptr1, ind2 = *(const int*) ptr2;
	int d1 = data[ind1], d2 = data[ind2];
	if (d1 < d2)
		return -1;
	if (d1 > d2)
		return 1;
	return ind1 - ind2;
}

void process(size_t count, int *data, int *order) {
	if (!count)
		return;
	int i = 0;
	while (i != (int)count) {
		order[i] = i;
		i++;
	}
	qsort_r(order, count, sizeof(*order), comp, (void*)data);
}
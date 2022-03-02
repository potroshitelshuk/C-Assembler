#include<stdio.h>
#include<stdint.h>
#include<inttypes.h>


int bitcount(STYPE value) {  
	int cnt = 0;
	UTYPE val = value;
	while (val != 0) {
		if (val & 1)
			cnt += 1;
		val >>= 1;
	}
	return cnt;
};

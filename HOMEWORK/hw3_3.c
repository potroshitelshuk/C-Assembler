#include <stdio.h>

union U_u {
	float f;
	struct {
		unsigned frac:23; 
		unsigned exp:8;  
		unsigned sign:1;  
	};
};

FPClass fpclassf(float value, int *psign) {
	union U_u u;
	u.f = value;
	if (u.exp == 0xff && u.frac != 0) {
		*psign = 0;
		return FFP_NAN;
	}
	if (u.exp == 0xff && u.frac == 0) {
		*psign = u.sign;
		return FFP_INF;
	}
	if (u.exp == 0 && u.frac == 0) {
		*psign = u.sign;
		return FFP_ZERO;
	}
	if (u.exp == 0 && u.frac != 0) {
		*psign = u.sign;
		return FFP_DENORMALIZED;
	}
	*psign = u.sign;
	return FFP_NORMALIZED;
}
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

enum {
	A = 1103515245,
	C = 12345,
	MOD = 1 << 31
};

typedef struct RandomOperations {
	int (*next)(void *rg);
	void (*destroy)(void *rg);
} RandomOperations;

typedef struct RandomGenerator {
	long long x;
	RandomOperations *ops;
} RandomGenerator;

int next(void* rg_) {
	RandomGenerator *rg = rg_;
	rg->x = (rg->x * A + C) % MOD;
	return rg->x;
}

void destroy(void *rg_) {
	RandomGenerator *rg = rg_;
	free(rg->ops);
	free(rg);
}

RandomGenerator *random_create(int seed) {
	RandomGenerator *rg = malloc(sizeof(RandomGenerator));
	if (!rg) {
		fprintf(stderr, "bad malloc");
		exit(1);
	}
	rg->x = seed;
	rg->ops = malloc(sizeof(RandomOperations));
	if (rg->ops == NULL) {
		fprintf(stderr, "bad malloc");
		exit(1);
	}
	rg->ops->next = &next;
	rg->ops->destroy = &destroy;
	return rg;
}

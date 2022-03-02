#include <stddef.h>


struct BSearchResult {
	size_t low, high;
	int result;
};

struct BSearchResult
bsearch2(
        const void *key,
        const void *base,
        size_t nmemb,
        size_t size,
        int (*compar)(const void *p1, const void *p2, void *user),
        void *user) {
	struct BSearchResult ans = {0, 0, 0};
	size_t l = 0, r = nmemb;
	if (nmemb == 0)
		return ans; 
	while (r - 1 > l) {
		size_t avg = (r - l) / 2 + l;
		if (compar(avg * size + base, key, user) < 0) {
			l = avg;
		} else {
			r = avg;
		}
	}
	if (nmemb > 0 && compar(base + l * size, key, user) < 0)
		l += 1;
	ans.low = l;
	r = nmemb;
	l = 0;
	while (r - 1 > l) {
		size_t avg = (r - l) / 2 + l;
		if (compar(avg * size + base, key, user) <= 0) {
			l = avg;
		} else {
			r = avg;
		}
	}
	if (nmemb > 0 && compar(base + l * size, key, user) > 0)
		r -= 1;
	ans.high = r;
	ans.result = 0;
	if (ans.low != ans.high)
		ans.result = 1;
	return ans;
}


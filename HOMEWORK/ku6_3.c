#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>

int main (int argc, const char *argv[]) {
	int y, mth, d, period, i = 1;
	scanf("%d-%d-%d %d", &y, &mth, &d, &period);
	while (i != 2 * period + 1) {
		time_t t = 0;
		time(&t);
		struct tm * tm_ = localtime(&t);
		if (6*i % 12 == 0) {
		    tm_->tm_year = y - 1900 + (6 * i / 12);
		    tm_->tm_mon = mth - 1;
		} else {
		    tm_->tm_year = y - 1900 + (6 * (i - 1) / 12);
		    tm_->tm_mon = mth + 5;
		}
		tm_->tm_mday = d;
		mktime(tm_);
		if (tm_->tm_wday == 6)
			tm_->tm_mday += 2;
		if (tm_->tm_wday == 0)
			tm_->tm_mday += 1;
		mktime(tm_);
		printf("%04d-%02d-%02d\n", tm_->tm_year + 1900, tm_->tm_mon + 1, tm_->tm_mday);
		i += 1;
	}
	return 0;
}
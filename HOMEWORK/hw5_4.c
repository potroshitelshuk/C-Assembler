// Сделано на семинаре

#include <stdio.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>

int main() {
	setlocale(LC_ALL, "ru_RU.UTF-8");
	int cnt_d = 0, cnt_low = 0, cnt_up = 0;
	wint_t symb;
	while ((symb = fgetwc(stdin)) != EOF) {
		if (iswdigit(symb)) {
			cnt_d += 1;
		} else if (iswalpha(symb)) {
			if (iswupper(symb)) {
				cnt_up += 1;
			} else if (iswlower(symb)) {
				cnt_low += 1;
			}
		}
	}
	printf("%d\n%d\n%d\n", cnt_d, cnt_up, cnt_low);
	return 0;
}
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <ctype.h>

int main(int argc, char* argv[]) {
    FILE* input = stdin;
    if (argc == 2) {
        input = fopen(argv[1], "r");
        if (input == NULL) {
            fprintf(stderr, "file doesn't exist\n");
            return 1;
        }
    } else if (argc > 2) {
        fprintf(stderr, "too much files\n");
        return 1;
    }

    char word[64];
    word[0] = '\0';
    int max = ~(-1u>>1);
    double min = INFINITY;
    int counter = 0;
    int is_end = 0;
    int is_find[2] = {0, 0};
    int c;
    while ((c = getc(input)) != EOF) {
        if ((c >= 0 && c <= 31) || c == 127) {
            if (c != '\r' && c != '\t' && c != '\n') {
                fprintf(stderr, "bad input\n");
                return 1;
            }
        }

        if (isspace(c) && is_end) {
            counter = 0;
            is_end = 0;
            char* eptr;
            errno = 0;
            int64_t num1 = (int64_t) strtol(word, &eptr, 10);
            if (*eptr || (errno && errno != ERANGE)) {
                errno = 0;
                if (min == NAN) continue;
                char* eptr2;
                double num2 = strtod(word, &eptr2);
                if (num2 != num2) {
                    is_find[1] = 1;
                    min = NAN;
                }
                if (*eptr2 || errno) continue;

                if (min != NAN && (min > num2 || num2 == INFINITY)) {
                    min = num2;
                    is_find[1] = 1;
                }

            } else {
                if (errno == ERANGE) continue;
                else if (num1 == (int) num1 && num1 >= max) {
                    max = num1;
                    is_find[0] = 1;
                }
            }

            word[0] = '\0';
        }

        if (!isspace(c)) {
            if (counter == 63) {
                fprintf(stderr, "overflow\n");
                return 1;
            }

            is_end = 1;
            word[counter] = c;
            counter++;
            word[counter] = '\0';
        }
    }
    if (is_end) {
        counter = 0;
            is_end = 0;
            char* eptr;
            errno = 0;
            int64_t num1 = (int64_t) strtol(word, &eptr, 10);
            if (*eptr || (errno && errno != ERANGE)) {
                errno = 0;

                char* eptr2;
                double num2 = strtod(word, &eptr2);
                if (num2 != num2) {
                    min = NAN;
                    is_find[1] = 1;
                }

                if (!errno && !*eptr2 && min != NAN && (min > num2 || num2 == INFINITY)) {
                    min = num2;
                    is_find[1] = 1;
                }

            } else {
                if (errno != ERANGE && num1 == (int) num1 && num1 >= max) {
                    max = num1;
                    is_find[0] = 1;
                }
            }

            word[0] = '\0';
    }
    if (is_find[0] && is_find[1]) {
        printf("%d %.10g\n", max, min);
    } else {
        fprintf(stderr, "no double or int in input\n");
        return 1;
    }

    if (argc != 1) {
        fclose(input);
    }
    return 0;
}

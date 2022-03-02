#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <float.h>
#include <errno.h>
#include <math.h>
#include <ctype.h>

enum {
    BASE = 10
};

FILE* read_cmd(int argc, char* argv[]) {
    FILE* file = stdin;
    if (argc == 2) {
        file = fopen(argv[1], "r");
    } else if (argc > 2) {
        file = NULL;
    }
    return file;
}


int main(int argc, char* argv[]) {
    int end = 0;
    int was_nan = 0;
    int is_find[2] = {0, 0};
    int c;
    int is_end_of_file = 0;
    int cnt = 0;
    int i = 0;
    char s[64];
    int32_t max_int = INT32_MIN;
    double min_dbl = DBL_MAX;
    FILE* file = read_cmd(argc, argv);
    if (file == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    while ((c = fgetc(file)) != EOF) {
        if ((c >= 0 && c <= 31) || c == 127) {
            if (c != '\r' && c != '\t' && c != '\n') {
                fprintf(stderr, "Invalid input\n");
                return 1;
            }
        }

        if (isspace(c)) {
            end = 1;
            cnt = 0;
            s[i] = '\0';
        } else {
            if (cnt == 63) {
                fprintf(stderr, "Too much symb\n");
                return 1;
            }
            is_end_of_file = 1;
            s[i] = (c);
            cnt++;
            i++;
        }

        if (end) {
            const char *str = s;
            char *eptr;
            errno = 0;
            long x = strtol(str, &eptr, BASE);
            if (*str && !*eptr && !(errno && errno != ERANGE)) {
                if ((int32_t)(x) == x) {
                    is_find[0] = 1;
                    if (x > max_int)
                        max_int = x;
                }
            } else {
                char *eptr;
                errno = 0;
                double y = strtod(str, &eptr);
                printf("asdas%f\n", y);
                if (*str && !*eptr && !(errno && errno != ERANGE)) {
                    is_find[1] = 1;
                    if (y != y) {
                        min_dbl = NAN;
                        was_nan = 1;
                    }
                    if (y < min_dbl && !was_nan)
                        min_dbl = y;
                }
            }
            end = 0;
            i = 0;
            s[0] = '\0';
        }
    }
    if (is_end_of_file) {
        s[i] = '\0';
        const char *str = s;
        char *eptr;
        errno = 0;
        long x = strtol(str, &eptr, BASE);
        if (*str && !*eptr && !(errno && errno != ERANGE)) {
            if ((int32_t)(x) == x) {
                is_find[0] = 1;
                if (x > max_int)
                    max_int = x;
            }
        } else {
            char *eptr;
            errno = 0;
            double y = strtod(str, &eptr);
            if (*str && !*eptr && !(errno && errno != ERANGE)) {
                is_find[1] = 1;
                if (y != y) {
                    min_dbl = NAN;
                    was_nan = 1;
                }
                if (y < min_dbl && !was_nan)
                    min_dbl = y;
            }
        }
    }
    if (!is_find[0] || !is_find[1]) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    } else {
        printf("%" PRId32 " %.10g\n", max_int, min_dbl);
    }
}
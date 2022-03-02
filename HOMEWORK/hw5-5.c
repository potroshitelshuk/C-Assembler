#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>
#include <limits.h>
// Сделано на семинаре
enum {
    UTF2 = 0b11000000,
    UTF3 = 0b11100000,
    UTF4 = 0b11110000,
    BOARD_DELIMITER = 0x20,
    BASE = 32
    // CHAR_BIT, UCHAR_MAX
};
// ABCD
//  BCD // B , C: BC, D: BCD
//   CD
//    D
void update_symbol(uint32_t *symbol, int c) {
    *symbol = (*symbol << CHAR_BIT) + c;
}

int read_one_symbol(uint32_t *symbol) {
    int c = getchar();
    if (c == EOF) {
        return 0;
    }
    *symbol = c;
    // 110xxxxx 10xxxxxx, c = 110xxxxx
    if (c >= UTF2) {
        update_symbol(symbol, getchar());
    }
    // 1110xxxx 10xxxxxx 10xxxxxx, c = 1110xxxx
    if (c >= UTF3) {
        update_symbol(symbol, getchar());
    }
    
    if (c >= UTF4) {
        update_symbol(symbol, getchar());
    }
    return 1;
}

void write_one_symbol(uint32_t symbol) {
    if (symbol >> (3 * CHAR_BIT) >= UTF4) {
        putchar((symbol >> (3 * CHAR_BIT)) & UCHAR_MAX);
    }
    if (symbol >> (2 * CHAR_BIT) >= UTF3) {
        putchar((symbol >> (2 * CHAR_BIT)) & UCHAR_MAX);
    }
    if (symbol >> CHAR_BIT >= UTF2) {
        putchar((symbol >> CHAR_BIT) & UCHAR_MAX);
    }
    putchar(symbol & UCHAR_MAX);
}

typedef struct String {
    uint32_t* data;
    int length;
    int capacity;
} String;

String *createString() {
    String *s = malloc(sizeof(String));
    s->length = 0;
    s->capacity = BASE;
    s->data = calloc(BASE, sizeof(*s->data));
    return s;
}

void deleteString(String *s) {
    if (s) {
        if (s->data) {
            free(s->data);
        }
        free(s);
    }
}

String *pushBack(String *s, uint32_t symbol) {
    if (s->length == s->capacity) {
        //s->data = realloc(s->data, (s->capacity *= 2) * sizeof(*s->data));
        // if (s->data == NULL) {free(s->data);}
        uint32_t *tmp = realloc(s->data, (s->capacity *= 2) * sizeof(*s->data));
        if (tmp == NULL) {
            fprintf(stderr, "bad realloc");
            deleteString(s);
            exit(1);
        }
        s->data = tmp;
    }
    s->data[s->length++] = symbol;
    return s;
}

int main() {
    String *large = createString();
    String *tmp = createString();
    uint32_t symbol;

    while(read_one_symbol(&symbol)) {
        if (symbol > BOARD_DELIMITER) {
            tmp = pushBack(tmp, symbol);
        } else {
            if (large != tmp) {
                deleteString(tmp);
            }
            tmp = createString();
        }
        if (large->length < tmp->length) {
            deleteString(large);
            large = tmp;
        }
    }
    printf("%d\n", large->length);
    for (int i = 0; i < large->length; i++) {
        write_one_symbol(large->data[i]);
    }
    deleteString(large);
    printf("\n");
    return 0;
}




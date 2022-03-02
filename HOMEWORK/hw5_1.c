#include <stdio.h>
#include <stdlib.h>
// Шаблон с семинара
struct Arr {
    int val;
    struct Arr* next;
};

int main() {
    struct Arr* head = NULL;
    int x;
    while (scanf("%d", &x) != EOF) {
        struct Arr* elem = calloc(1, sizeof(*elem));
        elem -> val = x;
        elem -> next = head;
        head = elem;
    }
    while (head) {
        printf("%d\n", head -> val);
        struct Arr* ptr = head;
        head = head -> next;
        free(ptr);
    }
}
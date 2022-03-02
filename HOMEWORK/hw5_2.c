#include <stdio.h>
#include <stdlib.h>
struct Arr* head = NULL;
int is_new = 0;
struct pair {
    int count;
    int value;
    
};

struct Arr {
    struct pair num;
    struct Arr* next;
    struct Arr* prev;
};



struct Arr* find(int x) {
    is_new = 0;
    struct Arr* tmp = head;
    while (tmp && tmp -> num.value != x) {
        tmp = tmp -> next;
    }

    if (tmp && tmp -> num.value == x) {
        return tmp; // Возврат на найденный элемент
    }   
    is_new = 1;
    return head; // Возврат на голову если не нашли элемент


}
 // -> 2
 // 1 <-> 2 <-> 3
void push(int x) {
    struct Arr* tmp = find(x);
    if (tmp == head && is_new) {
        struct Arr* elem = calloc(1, sizeof(*elem));
        elem -> num.value = x;
        elem -> num.count = 1;
        elem -> next = head;
        if (head)
            head -> prev = elem;
        head = elem;
    } else {
        tmp -> num.count += 1;
        if (tmp != head) {
            if (tmp -> next)
                tmp -> next -> prev = tmp -> prev;
            if (tmp -> prev)
                tmp -> prev -> next = tmp -> next;
            head -> prev = tmp;
            tmp -> prev = NULL;
            tmp -> next = head;
            head = tmp;
        }
    }    
}

int main() {
    int x;
    while (scanf("%d", &x) != EOF) {
        push(x);
    }

    while (head && head -> next)
        head = head -> next;
    
    while (head && head -> prev) {
        printf("%d %d\n", head -> num.value, head -> num.count);
        struct Arr* ptr = head;
        head = head -> prev;
        free(ptr);
    }

    if (head) {
        printf("%d %d\n", head -> num.value, head -> num.count);
        free(head);
    }
}
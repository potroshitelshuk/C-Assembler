#include <stdio.h>
#include <stdlib.h>

struct Node* root = NULL;

struct Node {
    int n;
    struct Node* left;
    struct Node* right;
};


void push(int x) {
    struct Node* elem = calloc(1, sizeof(*elem));
    struct Node* temp = root;
    elem -> n = x;
    elem -> left = NULL;
    elem -> right = NULL;
    if (root == NULL) {
        root = elem;
    } else  {
        while (temp -> left != NULL || temp -> right != NULL) {
            if (x < temp -> n) {
                if (temp -> left != NULL) {
                    temp = temp -> left;
                } else {
                    temp -> left = elem;
                    break;
                }
            } else {
                if (x > temp -> n) {
                    if (temp -> right != NULL) {
                        temp = temp -> right;
                    } else {
                        temp -> right = elem;
                        break;
                    }
                } else {
                    free(elem);
                    break;
                }
            }
        }
        if (temp -> left == NULL && temp -> right == NULL) {
            if (x < temp -> n)
                temp -> left = elem;
            if (x > temp -> n)
                temp -> right = elem;
        }
    }
}

void print_tree(struct Node* root) {
    if (root != NULL) {
        if (root -> right != NULL) {
        print_tree(root -> right);
        }
        if (root -> left != NULL) {
            printf("%d ", root -> n);
            print_tree(root -> left);
        } else {
            printf("%d ", root -> n);
        }
        free(root);
    }
}

int main() {
    int x;
    int fl = 0;
    while (scanf("%d", &x) != EOF) {
        if (x != 0) {
            push(x);
            fl = 0;
        } else {
            fl = 1;
            print_tree(root);
            printf("%d\n", 0);
            root = NULL; 
        }
    }
    if (fl == 0 && root) {
        print_tree(root);
        printf("%d\n", 0);
    }
}
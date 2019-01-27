#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    struct Node *next;
    int data;
} Node;

int main() {
    int number;
    Node *head = NULL;
    while (scanf("%d", &number) == 1) {
        Node *new_node = malloc(sizeof(*head));
        new_node->data = number;
        new_node->next = head;
        head = new_node;
    }
    while (head) {
        printf("%d\n", head->data);
        void *to_delete = head;
        head = head->next;
        free(to_delete);
    }
    return 0;
}


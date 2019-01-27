#include <stdlib.h>
#include <stdio.h>

enum { HEAD_TO_TAIL = 0, TAIL_TO_HEAD = 1 };

typedef struct Node
{
    struct Node *prev, *next;
    int key;
    size_t count;
} Node;

Node *get_node(Node *head, Node *tail, int key) {
    Node *iterator;
    for (iterator = head; iterator; iterator = iterator->next) {
        if (iterator->key == key) {
            return iterator;
        }
    }
    return iterator;
}

void add_to_list(Node **head, Node **tail, int key) {
    Node *found_node = NULL;
    if (*head) {
        if ((found_node = get_node(*head, *tail, key)) != NULL) {
            ++(found_node->count);
            if (found_node == *head) {
                return;
            } else if (found_node == *tail) {
                // Tail is previous one.
                found_node->prev->next = NULL;
                *tail = found_node->prev;
                // Make it the head.
                found_node->prev = NULL;
                found_node->next = *head;
                (*head)->prev = found_node;
                *head = found_node;
            } else if (found_node != *head){
                // Unwrap.
                found_node->prev->next = found_node->next;
                found_node->next->prev = found_node->prev;
                // Make it the head.
                found_node->prev = NULL;
                found_node->next = *head;
                (*head)->prev = found_node;
                *head = found_node;
            }
        } else {
            // New node.
            Node *new_node = malloc(sizeof(**head));
            if (new_node) {
                new_node->key = key;
                new_node->count = 1;
                new_node->prev = NULL;
                new_node->next = *head;
                (*head)->prev = new_node;
                *head = new_node;
            }
        }
    } else {
        // Create first node.
        Node *new_node = malloc(sizeof(**head));
        if (new_node) {
            *head = new_node;
            *tail = new_node;
            new_node->key = key;
            new_node->count = 1;
            new_node->prev = NULL;
            new_node->next = NULL;
        }
    }
}

void print_list(Node *head, Node *tail, int direction) {
    if (direction == TAIL_TO_HEAD) {
        while (tail) {
            printf("%d %zu\n", tail->key, tail->count);
            tail = tail->prev;
        }
    } else {
        // HEAD_TO_TAIL
        while (head) {
            printf("%d %zu\n", head->key, head->count);
            head = head->next;
        }
    }
}

void free_list(Node *head, Node *tail) {
    if (head) {
        head = head->next;
        while (head) {
            free(head->prev);
            head = head->next;
        }
        free(tail);
    }
}

int main() {
    int key;
    Node *head = NULL, *tail = NULL;
    while (scanf("%d", &key) == 1) {
        add_to_list(&head, &tail, key);
    }
    print_list(head, tail, TAIL_TO_HEAD);
    free_list(head, tail);

    return 0;
}


#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    struct Node *left, *right;
    int data;
} Node;

void add_to_tree(Node **root, int key) {
    if (*root) {
        Node *node = *root;
        while (node->data != key) {
            if (key < node->data) {
                if (node->left) {
                    node = node->left;
                    continue;
                } else {
                    Node *new_node = malloc(sizeof(**root));
                    if (new_node) {
                        new_node->data = key;
                        new_node->left = NULL;
                        new_node->right = NULL;
                        node->left = new_node;
                    }
                    return;
                }
            }
            if (node->data < key) {
                if (node->right) {
                    node = node->right;
                    continue;
                } else {
                    Node *new_node = malloc(sizeof(**root));
                    if (new_node) {
                        new_node->data = key;
                        new_node->left = NULL;
                        new_node->right = NULL;
                        node->right = new_node;
                    }
                    return;
                }
            }
            if (node->data == key) {
                return;
            }
        }
    } else {
        // Tree is empty.
        *root = malloc(sizeof(**root));
        if (*root) {
            (*root)->data = key;
            (*root)->left = NULL;
            (*root)->right = NULL;
        }
    }
}

void print_tree(Node* root) {
    if (root) {
        print_tree(root->right);
        printf("%d ", root->data);
        print_tree(root->left);
    }
}

void free_tree(Node* root) {
    if (root) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

int main() {
    int key;
    Node *root = NULL;
    while (scanf("%d", &key) == 1) {
        if (key) {
            add_to_tree(&root, key);
        } else {
            print_tree(root);
            printf("0 ");
            free_tree(root);
            root = NULL;
        }
    }
    if (root) {
        // Last sequence may not end with 0.
        print_tree(root);
        printf("0");
        free_tree(root);
    }
    printf("\n");

    return 0;
}


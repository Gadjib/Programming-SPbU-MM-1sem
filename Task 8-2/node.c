#include "node.h"
#include <stdlib.h>
#include <string.h>

struct Node 
{
    char *key;
    char *value;
    int height;
    struct Node *left;
    struct Node *right;
};

int height(struct Node *node) 
{
    if (node == NULL)
        return 0;
    return node->height;
}

int balance_factor(struct Node *node) 
{
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

struct Node *right_rotate(struct Node *y) 
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    return x;
}

struct Node *left_rotate(struct Node *x) 
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));

    return y;
}

struct Node *new_node(char *key, char *value) 
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->key = strdup(key);
    node->value = strdup(value);
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

struct Node *insert(struct Node *node, char *key, char *value) 
{
    if (node == NULL)
    {
        return new_node(key, value);
    }
    if (strcmp(key, node->key) < 0)
    {
        node->left = insert(node->left, key, value);
    }
    else if (strcmp(key, node->key) > 0)
    {
        node->right = insert(node->right, key, value);
    }
    else 
    { 
        free(node->value);
        node->value = strdup(value);
        return node;
    }

    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));

    int balance = balance_factor(node);

    if (balance > 1 && strcmp(key, node->left->key) < 0)
    {
        return right_rotate(node);
    }
    if (balance < -1 && strcmp(key, node->right->key) > 0)
    {
        return left_rotate(node);
    }
    if (balance > 1 && strcmp(key, node->left->key) > 0) 
    {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    if (balance < -1 && strcmp(key, node->right->key) < 0) 
    {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;
}

struct Node *min_value_node(struct Node *node) 
{
    struct Node *current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

struct Node *delete_node(struct Node *root, char *key) 
{
    if (root == NULL)
    {
        return root;
    }
    if (strcmp(key, root->key) < 0)
    {
        root->left = delete_node(root->left, key);
    }
    else if (strcmp(key, root->key) > 0)
    {
        root->right = delete_node(root->right, key);
    }
    else 
    {
        if (root->left == NULL) 
        {
            struct Node *temp = root->right;
            free(root->key);
            free(root->value);
            free(root);
            return temp;
        } 
        else if (root->right == NULL) 
        {
            struct Node *temp = root->left;
            free(root->key);
            free(root->value);
            free(root);
            return temp;
        }

        struct Node *temp = min_value_node(root->right);

        free(root->key);
        free(root->value);
        root->key = strdup(temp->key);
        root->value = strdup(temp->value);

        root->right = delete_node(root->right, temp->key);
    }

    root->height = 1 + (height(root->left) > height(root->right) ? height(root->left) : height(root->right));

    int balance = balance_factor(root);

    if (balance > 1 && balance_factor(root->left) >= 0)
    {
        return right_rotate(root);
    }
    if (balance < -1 && balance_factor(root->right) <= 0)
    {
        return left_rotate(root);
    }
    if (balance > 1 && balance_factor(root->left) < 0) 
    {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    if (balance < -1 && balance_factor(root->right) > 0) 
    {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

char *search(struct Node *root, char *key) 
{
    if (root == NULL)
    {
        return NULL;
    }
    if (strcmp(key, root->key) == 0)
    {
        return root->value;
    }
    if (strcmp(key, root->key) < 0)
    {
        return search(root->left, key);
    }
    return search(root->right, key);
}

void free_tree(struct Node *root) 
{
    if (root != NULL) 
    {
        free_tree(root->left);
        free_tree(root->right);
        free(root->key);
        free(root->value);
        free(root);
    }
}
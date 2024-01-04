#pragma once

#include <stdio.h>

struct Node;

int height(struct Node *node);
int balance_factor(struct Node *node);
struct Node *right_rotate(struct Node *y);
struct Node *left_rotate(struct Node *x);
struct Node *new_node(char *key, char *value);
struct Node *insert(struct Node *node, char *key, char *value);
struct Node *min_value_node(struct Node *node);
struct Node *delete_node(struct Node *root, char *key);
char *search(struct Node *root, char *key);
void free_tree(struct Node *root);
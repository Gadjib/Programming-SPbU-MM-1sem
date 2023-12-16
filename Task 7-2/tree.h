#pragma once

#include <stdio.h>

struct TreeNode;

struct TreeNode *createNode(char operator, int number);
struct TreeNode *buildTree(FILE *file);
int evaluateExpression(struct TreeNode *root);
void printExpressionTree(struct TreeNode *root);
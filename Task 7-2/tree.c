#include "tree.h"
#include <stdlib.h>

struct TreeNode 
{
    char operator; 
    int number;   
    struct TreeNode *left;  
    struct TreeNode *right; 
};

struct TreeNode *createNode(char operator, int number) 
{
    struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    newNode->operator = operator;
    newNode->number = number;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct TreeNode *buildTree(FILE *file) 
{
    char token;
    int number = 0;
    fscanf(file, " %c", &token); 
    if (token == '(') 
    {
        fscanf(file, " %c", &token);
        struct TreeNode *node = createNode(token, 0);
        node->left = buildTree(file);
        node->right = buildTree(file);
        fscanf(file, " %c", &token); 
        return node;
    } 
    else 
    {
        ungetc(token, file); 
        fscanf(file, " %d", &number);
        return createNode('n', number);
    }
}

int evaluateExpression(struct TreeNode *root) 
{
    if (root->operator == 'n') 
    {
        return root->number;
    } 
    else 
    {
        int leftValue = evaluateExpression(root->left);
        int rightValue = evaluateExpression(root->right);
        switch (root->operator) 
        {
            case '+':
                return leftValue + rightValue;
            case '-':
                return leftValue - rightValue;
            case '*':
                return leftValue * rightValue;
            case '/':
                return leftValue / rightValue;
        }
    }
    return 0;
}

void printExpressionTree(struct TreeNode *root) 
{
    if (root == NULL) 
    {
        return;
    }

    if (root->operator == 'n') 
    {
        printf("%d", root->number);
    } 
    else 
    {
        printf("(%c ", root->operator);
        printExpressionTree(root->left);
        printf(" ");
        printExpressionTree(root->right);
        printf(")");
    }
}

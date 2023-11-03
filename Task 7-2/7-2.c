#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main() 
{
    FILE *file = fopen("7-2.txt", "r");
    if (file == NULL) 
    {
        perror("Ошибка открытия файла");
        return 1;
    }

    struct TreeNode *root = buildTree(file);

    fclose(file);

    printf("Дерево выражения: ");
    printExpressionTree(root);
    printf("\n");

    int result = evaluateExpression(root);
    printf("Результат вычисления: %d\n", result);

    return 0;
}
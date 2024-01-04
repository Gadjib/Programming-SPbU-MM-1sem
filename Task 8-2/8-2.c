#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

void display_menu() 
{
    printf("\n1. Добавить значение по ключу\n");
    printf("2. Получить значение по ключу\n");
    printf("3. Проверить наличие ключа\n");
    printf("4. Удалить ключ и связанное с ним значение\n");
    printf("5. Выйти\n");
    printf("Выберите операцию (1-5): ");
}

int main() 
{
    struct Node *root = NULL;
    int choice;
    char key[100], value[100];

    do 
    {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Введите ключ: ");
                scanf("%s", key);
                printf("Введите значение: ");
                scanf("%s", value);
                root = insert(root, key, value);
                printf("Значение успешно добавлено в словарь\n");
                break;
            case 2:
                printf("Введите ключ для поиска значения: ");
                scanf("%s", key);
                if (search(root, key) != NULL)
                    printf("Найденное значение: %s\n", search(root, key));
                else
                    printf("Ключ не найден в словаре\n");
                break;
            case 3:
                printf("Введите ключ для проверки наличия: ");
                scanf("%s", key);
                if (search(root, key) != NULL)
                    printf("Ключ присутствует в словаре\n");
                else
                    printf("Ключ отсутствует в словаре\n");
                break;
            case 4:
                printf("Введите ключ для удаления: ");
                scanf("%s", key);
                root = delete_node(root, key);
                printf("Ключ и связанное с ним значение успешно удалены из словаря\n");
                break;
            case 5:
                printf("Программа завершена\n");
                break;
            default:
                printf("Неверный ввод. Пожалуйста, выберите операцию от 1 до 5\n");
        }

    } while (choice != 5);

    free_tree(root);

    return 0;
}
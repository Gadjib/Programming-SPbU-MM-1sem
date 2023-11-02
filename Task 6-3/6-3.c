#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING_SIZE 100
#define MAX_NAME_SIZE 85
#define MAX_PHONE_SIZE 15

struct Contact 
{
    char name[MAX_NAME_SIZE];
    char phone[MAX_PHONE_SIZE];
};

int compareStrings(const char *string1, const char *string2) 
{
    while (*string1 && *string2) 
    {
        if (tolower(*string1) != tolower(*string2)) 
        {
            return tolower(*string1) - tolower(*string2);
        }
        string1++;
        string2++;
    }
    return tolower(*string1) - tolower(*string2);
}

void merge(struct Contact *array, int left, int mid, int right, int choice) 
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    struct Contact *contactLeft = (struct Contact *)malloc(n1 * sizeof(struct Contact));
    struct Contact *contactRight = (struct Contact *)malloc(n2 * sizeof(struct Contact));

    for (int i = 0; i < n1; i++) 
    {
        contactLeft[i] = array[left + i];
    }
    for (int j = 0; j < n2; j++) 
    {
        contactRight[j] = array[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) 
    {
        if ((choice == 1 && compareStrings(contactLeft[i].name, contactRight[j].name) <= 0) ||
            (choice == 2 && compareStrings(contactLeft[i].phone, contactRight[j].phone) <= 0)) 
        {
            array[k] = contactLeft[i];
            i++;
        } 
        else
        {
            array[k] = contactRight[j];
            j++;
        }
        k++;
    }

    while (i < n1) 
    {
        array[k] = contactLeft[i];
        i++;
        k++;
    }

    while (j < n2) 
    {
        array[k] = contactRight[j];
        j++;
        k++;
    }

    free(contactLeft);
    free(contactRight);
}

void mergeSort(struct Contact *array, int left, int right, int choice) 
{
    if (left < right) 
    {
        int mid = left + (right - left) / 2;

        mergeSort(array, left, mid, choice);
        mergeSort(array, mid + 1, right, choice);

        merge(array, left, mid, right, choice);
    }
}

void printContacts(struct Contact *array, int size) 
{
    for (int i = 0; i < size; i++) 
    {
        printf("Имя: %s, Телефон: %s\n", array[i].name, array[i].phone);
    }
}

int main() 
{
    FILE *file = fopen("6-3.txt", "r");
    if (file == NULL) 
    {
        perror("Ошибка открытия файла");
        return 1;
    }

    struct Contact *contacts = NULL;
    int numContacts = 0;
    char line[MAX_STRING_SIZE]; 

    while (fgets(line, sizeof(line), file) != NULL) 
    {
        char *name = strtok(line, " -\n");
        char *phone = strtok(NULL, "\n");
        if (name != NULL && phone != NULL) 
        {
            while (*phone == ' ' || *phone == '-') 
            {
                phone++;
            }
            numContacts++;
            contacts = realloc(contacts, numContacts * sizeof(struct Contact));
            
            strcpy(contacts[numContacts - 1].name, name);
            strcpy(contacts[numContacts - 1].phone, phone);
        }
    }

    printf("Неотсортированные контакты:\n");
    printContacts(contacts, numContacts);

    int choice = 0;
    printf("\nВыберите, как сортировать: 1 для сортировки по имени, 2 для сортировки по телефону: ");
    scanf("%d", &choice);

    mergeSort(contacts, 0, numContacts - 1, choice);

    printf("\nОтсортированные контакты:\n");
    printContacts(contacts, numContacts);

    fclose(file);
    free(contacts);
    return 0;
}
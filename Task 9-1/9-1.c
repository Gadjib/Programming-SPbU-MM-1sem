#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 1000 
#define WORD_SIZE 100

struct Word 
{
    char word[WORD_SIZE];
    int frequency;
    struct Word *next;
};

struct HashTable 
{
    struct Word *table[TABLE_SIZE];
};

void initializeHashTable(struct HashTable *hashTable) 
{
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable->table[i] = NULL;
    }
}

unsigned int hash(const char *word) 
{
    unsigned int hash = 0;
    while (*word) 
    {
        hash = (hash * 31) + *word;
        word++;
    }
    return hash % TABLE_SIZE;
}

void insertWord(struct HashTable *hashTable, const char *word) 
{
    unsigned int index = hash(word);
    struct Word *current = hashTable->table[index];
    while (current != NULL) 
    {
        if (strcmp(current->word, word) == 0) 
        {
            current->frequency++;
            return;
        }
        current = current->next;
    }
    struct Word *newWord = (struct Word *)malloc(sizeof(struct Word));
    strcpy(newWord->word, word);
    newWord->frequency = 1;
    newWord->next = hashTable->table[index];
    hashTable->table[index] = newWord;
}

float loadFactor(struct HashTable *hashTable) 
{
    int count = 0;
    for (int i = 0; i < TABLE_SIZE; i++) 
    {
        struct Word *current = hashTable->table[i];
        while (current != NULL) 
        {
            count++;
            current = current->next;
        }
    }
    return (float)count / TABLE_SIZE;
}

void printHashTable(struct HashTable *hashTable) 
{
    for (int i = 0; i < TABLE_SIZE; i++) 
    {
        struct Word *current = hashTable->table[i];
        while (current != NULL) 
        {
            printf("%s: %d\n", current->word, current->frequency);
            current = current->next;
        }
    }
}

void maxAndAverageListLength(struct HashTable *hashTable, int *maxListLength, float *averageListLength) 
{
    *maxListLength = 0;
    int totalListLength = 0;
    for (int i = 0; i < TABLE_SIZE; i++) 
    {
        struct Word *current = hashTable->table[i];
        int listLength = 0;
        while (current != NULL) 
        {
            listLength++;
            current = current->next;
        }
        if (listLength > *maxListLength) 
        {
            *maxListLength = listLength;
        }
        totalListLength += listLength;
    }
    *averageListLength = (float)totalListLength / TABLE_SIZE;
}

int main() 
{
    FILE *file = fopen("9-1.txt", "r");
    if (file == NULL)
    {
        perror("Ошибка открытия файла");
        return 1;
    }

    struct HashTable hashTable;
    initializeHashTable(&hashTable);

    char word[WORD_SIZE] = " ";
    while (fscanf(file, "%s", word) != EOF) 
    {
        insertWord(&hashTable, word);
    }

    fclose(file);

    printf("Слова и их частоты встречаемости:\n");
    printHashTable(&hashTable);

    int maxListLenght = 0;
    float averageListLenght = 0;

    maxAndAverageListLength(&hashTable, &maxListLenght, &averageListLenght);
    
    printf("Коэффициент заполнения: %.2f\n", loadFactor(&hashTable));
    printf("Максимальная длина списка в сегменте таблицы: %d\n", maxListLenght);
    printf("Средняя длина списка в сегменте таблицы: %.2f\n", averageListLenght);

    return 0;
}

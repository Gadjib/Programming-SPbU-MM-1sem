#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void swapp(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Реализация сортировки вставками
void insertSort(int array[], int start, int end)
{
    if (start >= end)
    {
        return;
    }
    
    int element, location;

    for (int i = start; i < end; i++)
    {
        element = array[i];
        location = i - 1;

        while (location >= 0 && array[location] > element)
        {
            array[location + 1] = array[location];
            location = location - 1;
        }

        array[location + 1] = element;
    }
}

// Функция, разделяющая массив относительно точки опоры
int partition(int array[], int start, int end)
{
    int pivot = array[end - 1];
    int index = start;

    for (int i = start; i < end; i++)
    {   
        if (array[i] <= pivot)
        {
            swapp(&array[i], &array[index]);
            index++;
        }
    }
    
    swapp (&array[index], &array[end - 1]);
    return index;
}

// Сама функция qSort
void quickSort(int array[], int start, int end)
{
    if (start >= end)
    {
        return;
    }

    if (end - start < 10)
    {
        insertSort(array, start, end);
    }
    else
    {
        int pivot = partition(array, start, end);
        quickSort(array, start, pivot - 1);
        quickSort(array, pivot + 1, end);
    }
}



bool arraysEqual(int array1[], int array2[], int len)
{
    bool result = true;

    for (int i = 0; i < len; i++)
    {
        if (! (array1[i] == array2 [i]))
        {
            result = false;
        }
    }

    return result;
}

bool test(int array[], int arraySorted[], int arrayLength)
{
    quickSort(array, 0, arrayLength);
    if (arraysEqual(array, arraySorted, arrayLength))
    {
        return true;
    }
    return false;
}

int main()
{
    int array1[] = {4, 1, 8, 5};
    int array1Sorted[] = {1, 4, 5, 8};
    int array1Length = 4;
    
    int array2[] = {0};
    int array2Sorted[] = {0};
    int array2Length = 1;
    
    int array3[] = {34, 2452, 143, 34, 134, 566, 3, 100, 1234, 1234, 34, 565, 544};
    int array3Sorted[] = {3, 34, 34, 34, 100, 134, 143, 544, 565, 566, 1234, 1234, 2452};
    int array3Length = 13;

    if (test(array1, array1Sorted, array1Length) && test(array2, array2Sorted, array2Length) && test(array3, array3Sorted, array3Length))
    {
        printf("Все тесты пройдены\n");
        return 0;
    }
    printf("Тесты не пройдены\n");
    return -1;
}
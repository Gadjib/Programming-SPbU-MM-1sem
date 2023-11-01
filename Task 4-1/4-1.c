#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#define SIZE_OF_NUMBERS 31

void decToBin(int number, int array[])
{
    if (number < 0)
    {
        number = (int)(pow(2, SIZE_OF_NUMBERS) + number);
    }

    for (int i = 0; i < SIZE_OF_NUMBERS; i++)
    {
        array[SIZE_OF_NUMBERS - 1 - i] = number & 1;
        number = number >> 1;
    }
}

void sum(int number1[], int number2[], int array[])
{
    int extraBit = 0;
    for (int i = SIZE_OF_NUMBERS - 1; i >= 0; i--)
    {
        array[i] = (number1[i] + number2[i] + extraBit ) % 2;
        extraBit = ((number1[i] + number2[i] + extraBit) >= 2) ? 1 : 0;
    }
}

int binToDec(int numberArray[])
{
    int number = 0;

    for (int i = 1; i < SIZE_OF_NUMBERS; i++)
    {
        number = number << 1;
        number = number + (numberArray[i] % 2);
    }

    return number;
}

void printIntArrayOfNumber(int array[], int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%d", array[i]);
    }
    printf("\n");
}

int main()
{
    int number1 = 0;
    int number2 = 0;

    int maxNumber = (int)pow(2, SIZE_OF_NUMBERS - 1) + 1;
    printf("Введите два числа: \n");
    scanf("%d", &number1);
    if (number1 >= maxNumber)
    {
        printf("Ошибка: больше 2**32\n");
        return -1;
    }
    scanf("%d", &number2);
    if (number2 >= maxNumber)
    {
        printf("Ошибка: больше 2**32\n");
        return -1;
    }

    printf("\n");

    int number1Array[SIZE_OF_NUMBERS];
    int number2Array[SIZE_OF_NUMBERS];

    decToBin(number1, number1Array);
    decToBin(number2, number2Array);

    printf("Первое число в двоичном представлении:   ");
    printIntArrayOfNumber(number1Array, SIZE_OF_NUMBERS);
    printf("Второе число в двоичном представлении:   ");
    printIntArrayOfNumber(number2Array, SIZE_OF_NUMBERS);

    printf("\n");

    int sumArray[SIZE_OF_NUMBERS];
    sum(number1Array, number2Array, sumArray);

    printf("Сложение их в столбик:\n ");
    printIntArrayOfNumber(number1Array, SIZE_OF_NUMBERS);
    printf("+\n ");
    printIntArrayOfNumber(number2Array, SIZE_OF_NUMBERS);
    printf("=\n ");
    printIntArrayOfNumber(sumArray, SIZE_OF_NUMBERS);

    printf("\n");

    int decSum;
    decSum = binToDec(sumArray);
    printf("Сумма в десятичном представлении:   ");
    printf("%d\n", decSum);
}
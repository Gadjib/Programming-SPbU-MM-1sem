#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#define SIZE_OF_NUMBERS (sizeof(int) * 8)

void decToBin(int number, int array[])
{
    for (size_t i = 0; i < SIZE_OF_NUMBERS; i++)
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

    for (size_t i = 1; i < SIZE_OF_NUMBERS; i++)
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

    printf("Введите два числа: \n");
    scanf("%d", &number1);
    scanf("%d", &number2);

    printf("\n");

    int number1Array[SIZE_OF_NUMBERS] = {0};
    int number2Array[SIZE_OF_NUMBERS] = {0};

    decToBin(number1, number1Array);
    decToBin(number2, number2Array);

    printf("Первое число в двоичном представлении:   ");
    printIntArrayOfNumber(number1Array, SIZE_OF_NUMBERS);
    printf("Второе число в двоичном представлении:   ");
    printIntArrayOfNumber(number2Array, SIZE_OF_NUMBERS);

    printf("\n");

    int sumArray[SIZE_OF_NUMBERS] = {0};
    sum(number1Array, number2Array, sumArray);

    printf("Сложение их в столбик:\n ");
    printIntArrayOfNumber(number1Array, SIZE_OF_NUMBERS);
    printf("+\n ");
    printIntArrayOfNumber(number2Array, SIZE_OF_NUMBERS);
    printf("=\n ");
    printIntArrayOfNumber(sumArray, SIZE_OF_NUMBERS);

    printf("\n");

    int decSum = binToDec(sumArray);
    printf("Сумма в десятичном представлении:   ");
    printf("%d\n", decSum);
}
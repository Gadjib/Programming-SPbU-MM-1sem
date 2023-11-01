#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#define sizeOfNumbers 20

void decToBin(int number, int array[])
{
    if (number < 0)
    {
        number = (int)(pow(2, sizeOfNumbers) + number);
    }

    for (int i = 0; i < sizeOfNumbers; i++)
    {
        array[sizeOfNumbers - 1 - i] = number & 1;
        number = number >> 1;
    }
}

void sum(int number1[], int number2[], int array[])
{
    int extraBit = 0;
    for (int i = sizeOfNumbers - 1; i >= 0; i--)
    {
        array[i] = (number1[i] + number2[i] + extraBit ) % 2;
        extraBit = ((number1[i] + number2[i] + extraBit) >= 2) ? 1 : 0;
    }
}

int binToDec(int numberArray[])
{
    int number = 0;
    int inverter = 0;
    int multiplier = 1;
    int increment = 0;

    if (numberArray[0] == 1)
    {
        inverter = 1;
        multiplier = -1;
        increment = 1;
    }

    for (int i = 1; i < sizeOfNumbers; i++)
    {
        number = number << 1;
        number = number + ((numberArray[i] + inverter) % 2);
    }

    number = number + increment;
    number = number * multiplier;

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
    int number1, number2;
    int maxNumber = (int)pow(2, sizeOfNumbers - 1) + 1;
    printf("Введите два числа: \n");
    scanf("%d", &number1);
    if (number1 >= maxNumber)
    {
        printf("Ошибка: меньше 2**20\n");
        return -1;
    }
    scanf("%d", &number2);
    if (number2 >= maxNumber)
    {
        printf("Ошибка: меньше 2**20\n");
        return -1;
    }

    printf("\n");

    int number1Array[sizeOfNumbers];
    int number2Array[sizeOfNumbers];

    decToBin(number1, number1Array);
    decToBin(number2, number2Array);

    printf("Первое число в двоичном представлении:   ");
    printIntArrayOfNumber(number1Array, sizeOfNumbers);
    printf("Второе число в двоичном представлении:   ");
    printIntArrayOfNumber(number2Array, sizeOfNumbers);

    printf("\n");

    int sumArray[sizeOfNumbers];
    sum(number1Array, number2Array, sumArray);

    printf("Сложение их в столбик:\n ");
    printIntArrayOfNumber(number1Array, sizeOfNumbers);
    printf("+\n ");
    printIntArrayOfNumber(number2Array, sizeOfNumbers);
    printf("=\n ");
    printIntArrayOfNumber(sumArray, sizeOfNumbers);

    printf("\n");

    int decSum;
    decSum = binToDec(sumArray);
    printf("Сумма в десятичном представлении:   ");
    printf("%d\n", decSum);
}
#include "road.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Функция для нахождения ближайшего незанятого города к заданному городу
int findNearestUnassignedCity(int *distances, int *assigned, int numCities) {
    int minDistance = INT_MAX;
    int nearestCity = -1;

    for (int i = 0; i < numCities; ++i) {
        if (!assigned[i] && distances[i] < minDistance) {
            minDistance = distances[i];
            nearestCity = i;
        }
    }

    return nearestCity;
}

// Функция для распределения городов между государствами
void distributeCities(int n, int m, struct Road *roads, int k, int *capitals) {
    // Инициализация массива расстояний и массива, указывающего на принадлежность государству
    int *distances = (int *)malloc(n * sizeof(int));
    int *assigned = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; ++i) {
        distances[i] = INT_MAX;
        assigned[i] = 0;
    }

    // Начинаем с городов-столиц
    for (int i = 0; i < k; ++i) {
        assigned[capitals[i]] = i + 1;
    }

    // Распределение остальных городов
    for (int i = 0; i < n - k; ++i) {
        int currentCity = findNearestUnassignedCity(distances, assigned, n);
        int currentState = assigned[currentCity];

        printf("Государство %d: %d ", currentState, currentCity);

        assigned[currentCity] = currentState;

        // Обновление расстояний
        for (int j = 0; j < m; ++j) {
            if (roads[j].city1 == currentCity || roads[j].city2 == currentCity) {
                int otherCity = (roads[j].city1 == currentCity) ? roads[j].city2 : roads[j].city1;

                if (!assigned[otherCity] && roads[j].length < distances[otherCity]) {
                    distances[otherCity] = roads[j].length;
                }
            }
        }

        printf("\n");
    }

    free(distances);
    free(assigned);
}
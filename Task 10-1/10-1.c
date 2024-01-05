#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "road.h"

int main() {
    int n, m, k;
    printf("Введите число городов и дорог: ");
    scanf("%d %d", &n, &m);

    struct Road *roads = (struct Road *)malloc(m * sizeof(struct Road));

    printf("Введите информацию о дорогах в формате: i j len\n");
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d", &roads[i].city1, &roads[i].city2, &roads[i].length);
    }

    printf("Введите число столиц: ");
    scanf("%d", &k);

    int *capitals = (int *)malloc(k * sizeof(int));
    printf("Введите номера столиц: ");
    for (int i = 0; i < k; ++i) {
        scanf("%d", &capitals[i]);
    }

    distributeCities(n, m, roads, k, capitals);

    free(roads);
    free(capitals);

    return 0;
}

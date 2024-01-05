#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Road {
    int city1;
    int city2;
    int length;
};

int findNearestUnassignedCity(int *distances, int *assigned, int numCities);
void distributeCities(int n, int m, struct Road *roads, int k, int *capitals);
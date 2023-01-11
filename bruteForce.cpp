#include "bruteForce.h"
#include "tour.h"
#include <iostream>
#include <climits>

BruteForce::BruteForce(int numCities, float** matrix) {
	this->numCities = numCities;
	this->matrix = matrix;
    initializePermArr();
}

float BruteForce::calcBestTour() {
    long long numPerms = generateFactorial(numCities - 1);
    float bestCost = static_cast<float>(INT_MAX) + 1;
    for (int i = 0; i < numPerms; ++i) {
        Tour obj(permArr, numCities);
        generatePerm();
        float cost = obj.calcTotalCost(matrix);
        if (bestCost > cost) {
            bestCost = cost;
        }
    }
    return bestCost;
}

void BruteForce::initializePermArr() {
	permArr = new int[numCities];
	for (int i = 0; i < numCities; ++i) {
		permArr[i] = i;
	}
}
void BruteForce::generatePerm() {
    int m, k, p, q;
    m = numCities - 2;
    while (permArr[m] > permArr[m + 1])
    {
        m = m - 1;
    }
    k = numCities - 1;
    while (permArr[m] > permArr[k])
    {
        k = k - 1;
    }
    swap(m, k);
    p = m + 1;
    q = numCities - 1;
    while (p < q)
    {
        swap(p, q);
        p++;
        q--;
    }
}

void BruteForce::swap(int start, int end) {
    int temp = permArr[start];
    permArr[start] = permArr[end];
    permArr[end] = temp;
}

long long BruteForce::generateFactorial(int input) {
    if (input < 0) {
        return -1;
    }
    else {
        long long fac = 1;
        for (int i = 1; i <= input; ++i) {
            fac *= i;
        }
        return fac;
    }
}
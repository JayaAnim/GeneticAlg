#include "population.h"
#include "tour.h"
#include <iostream>
#include <climits>

Population::Population() {
	tourCont = nullptr;
	numCities = -1;
	numTours = -1;
	numGenerations = -1;
	numMutated = -1;
    permArr = nullptr;
    matrix = nullptr;
}

Population::Population(int numCities, int numTours, int numGenerations, float percentMutated, float** matrix) {
	this->numCities = numCities;
	this->numTours = numTours;
	this->numGenerations = numGenerations;
    numMutated = numTours * percentMutated;
    this->matrix = matrix;
	tourCont = new Tour[numTours];
    initializePermArr();
    tourCont[0].replaceTour(permArr, numCities);
    for (int i = 1; i < numTours; ++i) {
        generatePerm();
        tourCont[i].replaceTour(permArr, numCities);
    }
}

float Population::findOptimalCost() {
    float bestCost = -1;
    for (int i = 0; i < numGenerations; ++i) {
        createNewGeneration();
        bestCost = tourCont[0].calcTotalCost(matrix);
    }
    return bestCost;
}

void Population::createNewGeneration() {
    Tour* newGen = new Tour[numTours];
    int numToMutate = numMutated / 2;
    int numToBreed = numMutated - numToMutate;
    int newGenIndex = 0, bestIndex;
    float bestCost = static_cast<float>(INT_MAX) + 1;
    for (int i = 0; i < numTours; ++i) {
        float cost = tourCont[i].calcTotalCost(matrix); // Increasing space complexity to save time complexity
        if (bestCost > cost) {
            bestCost = cost;
            bestIndex = i;
        }
    }
    newGen[newGenIndex] = tourCont[bestIndex]; // Keep best tour
    ++newGenIndex;
    if (numToMutate >= 1) { // Add mutated version of best tour if allowed
        newGen[newGenIndex] = newGen[0];
        newGen[newGenIndex].mutate();
        ++newGenIndex;
        --numToMutate;
    }
    for (int i = 0; i < numToMutate; ++i) { // Generate number of allotted mutations
        tourCont[newGenIndex].mutate();
        newGen[newGenIndex] = tourCont[newGenIndex];
        ++newGenIndex;
    }
    int tempIndex = 0;
    for (int i = 0; i < numToBreed; ++i) { // Generate number of allotted crossovers
        int* temp = tourCont[newGenIndex].generateOffspring(newGen[tempIndex].getPerm());
        newGen[newGenIndex].replaceTour(temp, numCities);
        delete[] temp;
        ++tempIndex;
        ++newGenIndex;
    }
    for (int i = newGenIndex; i < numTours; ++i) { // Generate permutations to fill rest of new generation
        generatePerm();
        newGen[i].replaceTour(permArr, numCities);
    }

    for (int i = 0; i < numTours; ++i) { // Replace old generation with new generaion
        tourCont[i] = newGen[i];
    }

    delete[] newGen;
}

void Population::generatePerm() {
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

void Population::swap(int start, int end) {
    int temp = permArr[start];
    permArr[start] = permArr[end];
    permArr[end] = temp;
}

void Population::initializePermArr() {
    permArr = new int[numCities];
    for (int i = 0; i < numCities; ++i) {
        permArr[i] = i;
    }
}

Population::~Population() {
    if (permArr != nullptr) {
        delete permArr;
    }
    if (tourCont != nullptr) {
        delete[] tourCont;
    }
}

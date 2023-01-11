#include "tour.h"
#include <iostream>
#include <vector>

Tour::Tour() {
    numCities = -1;
    perm = nullptr;
}

Tour::Tour(int* refPerm, int numCities) {
    this->numCities = numCities;
	perm = new int[numCities];
    for (int i = 0; i < numCities; ++i) {
        perm[i] = refPerm[i];
    }
}

Tour& Tour::operator=(const Tour& tour) {
       if (perm != nullptr) {
           delete[] perm;
       }
       numCities = tour.numCities;
       perm = new int[numCities];
       for (int i = 0; i < numCities; ++i) {
           perm[i] = tour.perm[i];
       }
       return *this;
}

void Tour::replaceTour(int* arr, int arrSize) {
    if (perm != nullptr) {
        delete[] perm;
    }
    numCities = arrSize;
    perm = new int [arrSize];
    for (int i = 0; i < arrSize; ++i) {
        perm[i] = arr[i];
    }

}

float Tour::calcTotalCost(float** matrix) {
    float cost = 0;
    
    for (int i = 0; i < numCities - 1; ++i) {
        cost += matrix[perm[i]][perm[i+1]];
    }
    return cost;
}

int* Tour::generateOffspring(int* parent) {
    int mid = numCities / 2;
    int* offspring = new int[numCities];
    int count = 0;
    for (int i = 0; i < mid; ++i) { // Fill front half of offspring with first parent
        offspring[i] = perm[i];
    }
    for (int i = mid; i < numCities; ++i) { // Fill back half of offspring with second parent
        offspring[i] = parent[i];
    }

    for (int i = 0; i < numCities; ++i) {
        for (int j = i + 1; j < numCities; ++j) {
            if (offspring[i] == offspring[j]) {
                ++count;
            }
        }
    }
    int* illegalIndices = new int[count];
    int* missingCities = new int[count];
    int index = 0;
    for (int i = 0; i < numCities; ++i) { // Find illegal indices 
        for (int j = i + 1; j < numCities; ++j) {
            if (offspring[i] == offspring[j]) {
                illegalIndices[index] = j;
                ++index;
            }
        }
    }

    index = 0;
    for (int i = 0; i < numCities; ++i) { // Find missing cities
        bool exists = false;
        for (int j = 0; j < numCities; ++j) {
            if (offspring[j] == i) {
                exists = true;
            }
        }
        if (!exists) {
            missingCities[index] = i;
            ++index;
        }
    }
 
    for (int i = 0; i < count; ++i) { // Fill illegal indices with missing cities
        
        offspring[illegalIndices[i]] = missingCities[i];
    }
    delete[] illegalIndices;
    delete[] missingCities;
    
    return offspring;
}

void Tour::mutate() {
    int i = numCities / 2;
    int j = numCities - 1;
    while (i != j && i < j) {
        swap(i, j);
        ++i;
        --j;
    }
}

int* Tour::getPerm() {
    return perm;
}

void Tour::swap(int val1, int val2) {
    int temp = perm[val1];
    perm[val1] = perm[val2];
    perm[val2] = temp;
}

Tour::~Tour() {
    if (perm != nullptr) {
        delete[] perm;
    }
}
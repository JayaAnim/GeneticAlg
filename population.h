#ifndef POPULATION_H
#define POPULATION_H
#include "tour.h"
#include <iostream>

class Population {
private: 
	Tour* tourCont;
	int numCities, numTours, numGenerations, numMutated; // number of cities to run (per tour), num of tours per generation, num of generations to run, num of tours to mutate per generation
	int* permArr; // permutation array
	float** matrix; // matrices of costs
public: 
	Population();
	Population(int numCities, int numTours, int numGenerations, float percentMutated, float** matrix);
	float findOptimalCost();
	void createNewGeneration();
	void generatePerm();
	void swap(int start, int end);
	void initializePermArr();
	~Population();
};

#endif

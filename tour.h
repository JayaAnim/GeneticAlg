#ifndef TOUR_H
#define TOUR_H
#include <iostream>

class Tour {
private:
	int* perm;
	int numCities;
public:
	Tour();
	Tour(int* refPerm, int numCities);
	Tour& operator=(const Tour& tour);
	void replaceTour(int* arr, int arrSize);
	float calcTotalCost(float** matrix);
	int* generateOffspring(int* parent);
	void mutate();
	int* getPerm();
	void swap(int val1, int val2);
	~Tour();
};

#endif
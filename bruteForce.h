#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

class BruteForce {
private: 
	int numCities;
	int* permArr;
	float** matrix;
public: 
	BruteForce(int numCities, float** matrix);
	float calcBestTour();
	void initializePermArr();
	void generatePerm();
	void swap(int start, int end);
	long long generateFactorial(int input);
};

#endif
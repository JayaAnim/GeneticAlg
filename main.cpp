#include "tourManager.h"
#include "tour.h"
#include "population.h"
#include "bruteForce.h"
#include <iostream>
#include <chrono>
#include <ctime>
using namespace std;

int main() {
	std::chrono::time_point<std::chrono::system_clock> start, end;

	int numCities, numTours, numGenerations;
	float percentMutations;
	cout << "Enter the number of cities to run: ";
	cin >> numCities;
	cout << "Enter the number of tours to run: ";
	cin >> numTours;
	cout << "Enter the number of generations to run: ";
	cin >> numGenerations;
	cout << "Enter the percentage to mutate: ";
	cin >> percentMutations;

	TourManager matrix("distances.txt");

	start = std::chrono::system_clock::now();
	Population tourPop(numCities, numTours, numGenerations, percentMutations, matrix.getMatrix());
	float gaCost = tourPop.findOptimalCost();
	cout << "GA solution: " << gaCost << endl;
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	cout << "Elapsed time of GA solution: " << elapsed_seconds.count() << "s" << endl;

	start = std::chrono::system_clock::now();
	BruteForce solution(numCities, matrix.getMatrix());
	float bfCost = solution.calcBestTour();
	cout << "Brute force solution: " << bfCost << endl;
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds2 = end - start;
	cout << "Elapsed time of brute force: " << elapsed_seconds2.count() << "s" << endl;

	cout << "Percent of optimal(GA): " << (bfCost / gaCost) * 100 << "%" << endl;

}

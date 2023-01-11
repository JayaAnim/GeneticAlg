#ifndef TOURMANAGER_H
#define TOURMANAGER_H
#include <iostream>
#include <string>
#include <fstream>

class TourManager {
private:
	std::ifstream iFile;
	float** matrix;
public:
	TourManager();
	TourManager(std::string fileName); // generates 20x20 matrix of costs between cities
	float** getMatrix();
	~TourManager();
};

#endif


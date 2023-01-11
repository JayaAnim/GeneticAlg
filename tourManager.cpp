#include "tourManager.h"
#include <iostream>
#include <string>
#include <fstream>

TourManager::TourManager() {
	matrix = nullptr;
}

TourManager::TourManager(std::string fileName) {
	matrix = nullptr;
	iFile.open(fileName);
	if (!iFile.is_open()) {
		std::cout << "File failed to open" << std::endl;
	}
	else {
		matrix = new float* [20];
		for (int i = 0; i < 20; ++i) {
			matrix[i] = new float[20];
		}
		while (!iFile.eof()) {
			for (int i = 0; i < 20; ++i) {
				for (int j = 0; j < 20; ++j) {
					if (i == j) {
						matrix[i][j] = 0;
					}
					else {
						iFile >> matrix[i][j];
					}
				}
			}
		}
	}
}

float** TourManager::getMatrix() {
	return matrix;
}

TourManager::~TourManager() {
	for (int i = 0; i < 20; ++i) {
		delete[] matrix[i];
	}
	delete[] matrix;
	iFile.close();
	if (iFile.is_open()) {
		std::cout << "File failed to close" << std::endl;
	}
}
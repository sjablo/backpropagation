#include "stdafx.h"

Statistics::Statistics()
{
}


Statistics::~Statistics()
{
}

double Statistics::randomNumber(int min, int max)
{
	double result = min + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (max - min)));
	return result;
}

void Statistics::shuffleWines()
{
	std::random_shuffle(Wine::wineList.begin(), Wine::wineList.end());
	for (int i = 0; i < Wine::wineList.size(); i++) {
		if (i <= 0.75*Wine::wineList.size()) Wine::trainingData.push_back(Wine::wineList[i]);
		else Wine::testData.push_back(Wine::wineList[i]);
	}
}

void Statistics::shuffleTrainingData()
{
	std::random_shuffle(Wine::trainingData.begin(), Wine::trainingData.end());
}

unsigned short int Statistics::outputAsNumber(std::vector<double> outputVector) //interpretacja wektora wyjœciowego sieci neuronowej jako int
{
	std::string booleanString;
	booleanString.append(std::to_string((int)std::round(outputVector[0])));
	booleanString.append(std::to_string((int)std::round(outputVector[1])));
	return std::bitset<2>(booleanString).to_ulong();
}
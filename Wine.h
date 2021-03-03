#pragma once
class Wine
{
public:
	int typeInt;
	std::vector<double> parameters, type;

	static std::vector<Wine> wineList, trainingData, testData;

	Wine(int type, double p1, double p2, double p3, double p4, double p5, double p6, double p7, double p8, double p9, double p10, double p11, double p12, double p13);
	~Wine();
};
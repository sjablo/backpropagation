#include "stdafx.h"

std::vector<Wine> Wine::wineList;
std::vector<Wine> Wine::trainingData;
std::vector<Wine> Wine::testData;

Wine::Wine(int type, double p1, double p2, double p3, double p4, double p5, double p6, double p7, double p8, double p9, double p10, double p11, double p12, double p13)
{
	this->typeInt = type;

	parameters.push_back(p1);
	parameters.push_back(p2);
	parameters.push_back(p3);
	parameters.push_back(p4);
	parameters.push_back(p5);
	parameters.push_back(p6);
	parameters.push_back(p7);
	parameters.push_back(p8);
	parameters.push_back(p9);
	parameters.push_back(p10);
	parameters.push_back(p11);
	parameters.push_back(p12);
	parameters.push_back(p13);

	if (type == 1) {
		this->type.push_back(0);
		this->type.push_back(1);
	}
	else if (type == 2) {
		this->type.push_back(1);
		this->type.push_back(0);
	}
	else {
		this->type.push_back(1);
		this->type.push_back(1);
	}
}

Wine::~Wine()
{
}
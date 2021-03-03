#include "stdafx.h"


std::vector<double> Matrix::operator*(std::vector<double> v)
{
	if (this->matrix[0].size() != v.size())
		throw "Macierze nie spelniaja warunku mno¿enia!"; //warunek wykonalnoœci mno¿enia

	std::vector<double> result; // this.size() x m[0].size()
	double sum;

	for (int col = 0; col < this->matrix.size(); col++) {
		sum = 0;
		for (int row = 0; row < v.size(); row++) {
			sum += this->matrix[col][row] * v[row];
		}
		result.push_back(sum);
	}

	return result;
}

bool Matrix::operator!=(Matrix m) //za³o¿enie - macierze s¹ równej wielkoœci
{
	for (int i = 0; i < m.matrix.size(); i++)
		for (int j = 0; j < m.matrix[0].size(); j++)
			if ((std::round(100*m.matrix[i][j])/100) != (std::round(100*((*this).matrix[i][j]))/100)) return true; //zmieniono warunek tak, aby sprawdzano równoœæ do dwóch miejsc po przecinku
	return false;
}

std::vector<double> Matrix::add(std::vector<double> v1, std::vector<double> v2)
{
	if (v1.size() != v2.size()) throw "Wektory nie sa rownej wielkosci";

	std::vector<double> result;
	for (int i = 0; i < v1.size(); i++) {
		result.push_back(v1[i] + v2[i]);
	}
	return result;
}


Matrix::Matrix()
{
}


Matrix::~Matrix()
{
}

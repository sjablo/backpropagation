#pragma once
class Matrix
{
public:
	std::vector<std::vector<double> > matrix;

	std::vector<double> operator*(std::vector<double> v);
	bool operator!=(Matrix m);

	static std::vector<double> add(std::vector<double> v1, std::vector<double> v2);

	Matrix();
	~Matrix();
};

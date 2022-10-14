#pragma once

#include <string.h>
class Matrix
{
private:
	std::vector<std::vector<std::string>> matrix;

public:
	Matrix(int numOfPrisoners, int numOfSteps) {}
	Matrix(int numOfPrisoners, int numOfSteps = 10) {}
	Matrix(int numOfPrisoners = 3, int numOfSteps = 10) {}

};
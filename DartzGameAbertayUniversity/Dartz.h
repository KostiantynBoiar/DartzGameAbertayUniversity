#pragma once
#include <random>

class Dartz
{
private:
	int percentage;
public:
	enum Throw
	{
		throwBullEnum = 0, 
		throwTrebleEnum = 1, 
		throwDoubleEnum = 2, 
		throwSingleEnum = 3
	};
	Dartz();
	Dartz(int percantage);
	int throwBull(int getPercantage);
	int throwTreble(int trebleD, int accuracyP);
	int throwDouble(int trebleD, int accuracyP);
	int throwSingle(int trebleD, int accuracyP);
	int getPercantage();
	void setPercentage(int getP);
};


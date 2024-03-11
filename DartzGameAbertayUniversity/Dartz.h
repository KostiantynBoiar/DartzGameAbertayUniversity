#pragma once
class Dartz
{
private:
	int percantage;
public:
	enum Throw
	{
		throwBullEnum = 0, 
		throwTrebleEnum = 1, 
		throwDoubleEnum = 2, 
		throwSingleEnum = 3
	};
	int throwBull(int getPercantage);
	int throwTreble(int trebleD, int accuracyP);
	int throwDouble(int trebleD);
	int throwSingle(int trebleD);
	int getPercantage();
	void setPercentage(int getP);
};


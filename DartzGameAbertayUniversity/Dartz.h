#pragma once
class Dartz
{
private:
	int percantage;
public:
	int throwBull(int getPercantage);
	int throwTreble(int trebleD, int accuracyP);
	int throwDouble(int trebleD);
	int throwSingle(int trebleD);
	int getPercantage();
	void setPercentage(int getP);
};


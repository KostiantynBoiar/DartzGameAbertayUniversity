#include "Dartz.h"
#include <random>

int Dartz::throwBull(int getPercantage)
{
	//  Throw for the bull with percent accuracy (20<p<85)

	int random = rand() % 100 + 1;

	if (random <= (getPercantage - 20))
	{
		return 50;
	}
	else if (random <= 85)
	{
		return 25;
	}
	else
	{
		return rand() % 20 + 1;
	}
}

int Dartz::throwTreble(int trebleD, int accuracyP)
{
	int bd[2][21] = { {0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
			   {0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1} };

	int r = rand() % 100 + 1;

	if (r <= accuracyP)
		return 3 * trebleD;
	else if (r <= 90)
		return trebleD;
	else if (r <= 93)
		return 3 * bd[0][trebleD];
	else if (r <= 96)
		return 3 * bd[1][trebleD];
	else if (r <= 98)
		return bd[0][trebleD];
	else
		return bd[1][trebleD];
}

int Dartz::throwDouble(int trebleD)
{
	int bd[2][21] = { {0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
			   {0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1} };
	int r = rand() % 100 + 1;

	if (r <= 80)
		return 2 * trebleD;
	else if (r <= 85)
		return 0;
	else if (r <= 90)
		return trebleD;
	else if (r <= 93)
		return 2 * bd[0][trebleD];
	else if (r <= 96)
		return 2 * bd[1][trebleD];
	else if (r <= 98)
		return bd[0][trebleD];
	else
		return bd[1][trebleD];
}

int Dartz::throwSingle(int trebleD)
{
	int bd[2][21] = { {0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
			   {0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1} };
	int r = rand() % 100 + 1;

	if (trebleD == 25) {		// outer bullseye has success rate of 80%
		if (r <= 80)
			return 25;
		else if (r <= 90)
			return 50;
		else
			return rand() % 20 + 1;
	}
	else			// we must be aiming for 1 to 20 single
		if (r <= 88)
			return trebleD;
		else if (r <= 92)
			return bd[0][trebleD];
		else if (r <= 96)
			return bd[1][trebleD];
		else if (r <= 98)
			return 3 * trebleD;
		else
			return 2 * trebleD;
}

int Dartz::getPercantage()
{
	return this->percantage;
}

void Dartz::setPercentage(int getP)
{
	this->percantage = getP;
}

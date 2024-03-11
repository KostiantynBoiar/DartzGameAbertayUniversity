#pragma once
#include <string>
#include <random>

class Player
{
private:
	std::string name;
	int score;
	int accuracy = rand() % 100 + 1;

public:
	Player();
	Player(std::string name, int score);
	std::string getName();
	void setName(std::string getName);
	int getScore();
	void setScore(int getScore);
	double getAccuracy();
	void setAccuracy(int accuracy);
};


#pragma once
#include <string>
#include <random>

class Player
{
private:
	std::string name;
	int score;
	int accuracy;
	int winCount;
	int iter = 0;
public:
	Player();
	Player(std::string name, int score, int accuracy);
	std::string getName();
	void setIter(int iter);
	int getIter();
	void setName(std::string getName);
	int getScore();
	void setScore(int getScore);
	double getAccuracy();
	void setAccuracy(int accuracy);
	int getWinCount();
	void setWinCount(int winCount);
};


#pragma once
#include <string>
class Player
{
private:
	std::string name;
	int score;
	double accuracy;
public:
	Player(std::string name, int score);
	std::string getName();
	void setName(std::string getName);
	int getScore();
	void setScore(int getScore);
	double getAccuracy();
	void setAccuracy(double accuracy);
};


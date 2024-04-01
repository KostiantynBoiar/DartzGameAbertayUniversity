#include "Player.h"

Player::Player(std::string name, int score, int accuracy)
{
    this->name = name;
    this->score = score;
    this->accuracy = accuracy;
}

std::string Player::getName()
{
    return this->name;
}

void Player::setName(std::string getName)
{
    this->name = getName;
}

int Player::getScore()
{
    return this->score;
}

Player::Player()
{
}

void Player::setScore(int getScore)
{
    this->score = getScore;
}

double Player::getAccuracy()
{
    return this->accuracy;
}

void Player::setIter(int iter)
{
    this->iter = iter;
}
int Player::getIter() 
{
    return this->iter;
}
int Player::getWinCount()
{
    return this->winCount;
}

void Player::setWinCount(int winCount)
{
    this->winCount = winCount;
}


void Player::setAccuracy(int accuracy)
{
    this->accuracy = accuracy;
}

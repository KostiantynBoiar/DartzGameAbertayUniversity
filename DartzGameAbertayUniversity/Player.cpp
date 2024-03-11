#include "Player.h"

Player::Player(std::string name, int score)
{
    this->name = name;
    this->score = score;
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

void Player::setScore(int getScore)
{
    this->score = getScore;
}

double Player::getAccuracy()
{
    return this->accuracy;
}

void Player::setAccuracy(double accuracy)
{
    this->accuracy = accuracy;
}

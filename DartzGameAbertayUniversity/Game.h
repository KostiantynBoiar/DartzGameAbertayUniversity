#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <list>
#include "Dartz.h"
#include "Player.h"
#include <cmath>
#include <iomanip>
#include <map>
#include <unordered_map>
#include <sstream>

class Game
{
private:
	Player player1;
	Player player2;
	Dartz dartz;
	std::string getResultKey(int joeSetsWon, int sidSetsWon);

public:

	Game();
	Game(Player& player1, Player& player2, Dartz& dartz);
	int playerTurn(Player& player, int lastScore);
	std::string playGame(Player& player1, Player& player2, bool boolPlayerTurn);

	// Table where player are able to get the best strategy
	std::unordered_map<int, std::string> strategyTable = {
	{70, "T20, T20, B0"},
	{167, "T20, T19, B0"},
	{164, "T20, T18, B0"},
	{103, "T17, S12, D20"},
	};

	/*
		That's a function where I will be parsing strategy table for build strategy for a player depends of his remaining score
		Every iteration I will return map with 3 throws, first value will type of first throw, second will aim of first throw etc.
	*/
	std::unordered_map<Dartz::Throw, int> parseTable(int remainingScore);

	// Function to simulate set of games for players
	std::pair<int, int> playSet(bool turn);

	Dartz getDartz();
	// Function to simulate the World Championships final
	//Format of output table is {Player1} : {Player2} Frequency
	/*
		Joe : Sid Frequency
			7 : 6 4%
			6 : 7 8%
			5 : 7 18%
			4 : 7 34%
			3 : 7 22%
			2 : 7 9%
			1 : 7 5%
	*/
	void simulateFinal(int numSets);

	// Function for calculating best score for player to get 32 or 40
	int calculateThrow(int threbleD, Player& player);
	~Game();

};
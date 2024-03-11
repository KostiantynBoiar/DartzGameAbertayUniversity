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


class Game
{
private:
	Player player1;
	Player player2;
	Dartz dartz;

public:
	Game();
	Game(Player& player1, Player& player2, Dartz& dartz);
	int playerTurn(Player &player);
	std::string playGame(Player& player1, Player& player2);

	// Function to simulate a set

	std::pair<int, int> playSet();

	// Function to simulate the World Championships final
	std::pair<int, int> simulateFinal(int numSets);

	//Function for drawing results in the table format
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
	std::list<std::pair<int, int>> resultsTable(std::pair<int, int> playSet);
	void drawResultsTable(const std::list<std::pair<int, int>>& results);

	~Game();
	
};


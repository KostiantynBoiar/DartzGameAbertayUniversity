#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <list>
class Game
{
public:
	int playerTurn(int score);
	std::string playGame();

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
};


#include "Game.h"
#include "Dartz.h"

int Game::playerTurn(int score)
{
    Dartz dartz;
    int dartsThrown = 0;
    while (score > 1 && dartsThrown < 3) {
        int dartScore = dartz.throwSingle();
        if (score - dartScore == 1) {
            break;
        }
        else if (score - dartScore >= 0) {
            score -= dartScore;
        }
        dartsThrown++;
    }
    return score;
}

std::string Game::playGame()
{
    return std::string();
}

std::pair<int, int> Game::playSet()
{
    return std::pair<int, int>();
}

std::pair<int, int> Game::simulateFinal(int numSets)
{
    return std::pair<int, int>();
}

std::list<std::pair<int, int>> Game::resultsTable(std::pair<int, int> playSet)
{
    return std::list<std::pair<int, int>>();
}

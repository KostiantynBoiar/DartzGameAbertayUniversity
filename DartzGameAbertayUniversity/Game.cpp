#include "Game.h"

Game::Game()
{
}

Game::Game(Player& player1, Player& player2, Dartz& dartz)
{
    this->player1 = player1;
    this->player2 = player2;
    this->dartz = dartz;
}

int Game::playerTurn(Player& player, int lastScore) {
    Dartz dartz;
    int remainingScore = lastScore;
    int bufferScore = lastScore;
    Dartz::Throw lastThrow;

    for (int i = 0; i < 3; i++) {

        int score = dartz.throwBull(player.getAccuracy()); // Adjust the dartboard sequence
        // Update lastThrow based on the type of throw
        if (score == 50)
            lastThrow = Dartz::Throw::throwBullEnum;
        else if (score % 2 == 0 && score != 0)
            lastThrow = Dartz::Throw::throwDoubleEnum;
        else if (score % 3 == 0 && score != 0)
            lastThrow = Dartz::Throw::throwTrebleEnum;
        else
            lastThrow = Dartz::Throw::throwSingleEnum;

        switch (remainingScore)
        {
        case 20:
            score = dartz.throwSingle(20);
        case 40:
            score = dartz.throwDouble(20);
        case 60:
            score = dartz.throwTreble(20, player.getAccuracy());
        default:
            break;
        }
        // Deduct score from remainingScore

        if (remainingScore > 1) remainingScore -= score;
        if (remainingScore == 1) return -1;
        if (remainingScore < 0) return bufferScore;
        if (remainingScore == 0) return 0;

    }
    player.setScore(remainingScore);
    return remainingScore;
}


std::string Game::playGame(Player& player1, Player& player2, bool boolPlayerTurn)
{
    Player* player;

    while (true) {
        int bufferScore;
        int result;
        int currentPlayer;

        if (boolPlayerTurn == true) {
            player = &player1;
        }
        else {
            player = &player2;
        }

        result = playerTurn((*player), player->getScore());
        bufferScore = player->getScore();
        if (result == -1) {

            boolPlayerTurn = !boolPlayerTurn;
            player->setScore(bufferScore);
        }


        if (result > 0)
        {
            boolPlayerTurn = !boolPlayerTurn;
            continue;
        }

        if (result == 0) {
            return player->getName();
        }

    }
}



std::pair<int, int> Game::playSet(bool turn) {

    int joeWins = 0;
    int sidWins = 0;

    for (int i = 0; i < 5; ++i) {
        std::string winner = playGame(this->player1, this->player2, turn);
        if (winner == "Joe") {
            joeWins++;
        }
        else {
            sidWins++;
        }
    }
    return std::make_pair(joeWins, sidWins);
}

void Game::simulateFinal(int numSets) {
    srand(time(nullptr)); // Seed the random number generator
    int joeSetsWon = 0;
    int sidSetsWon = 0;
    int totalGames = 0;
    std::map<std::string, double> result;

    for (int i = 0; i < numSets; i++) {

        bool turn = (rand() % 2 == 0);

        for (int i = 0; i < 13; i++) {
            if (joeSetsWon > 6 || sidSetsWon > 7) break;
            std::pair<int, int> res = playSet(turn);
            if (res.first > res.second) {
                joeSetsWon++;
            }
            else {
                sidSetsWon++;
            }
        }

        std::string key = getResultKey(joeSetsWon, sidSetsWon);
        if (result.find(key) == result.end()) {
            result[key] = 1;
        }
        else {
            result[key]++;
        }

        joeSetsWon = 0;
        sidSetsWon = 0;
        totalGames++;
    }

    std::cout << "Results:" << std::endl;
    for (const auto& pair : result) {
        std::cout << pair.first << " : " << (pair.second * 100)/totalGames << " %" << std::endl;
    }
    int maxGames = 0;
    std::string mostLikelyResult;
    for (const auto& pair : result) {
        if (pair.second > maxGames) {
            maxGames = pair.second;
            mostLikelyResult = pair.first;
        }
    }

    std::cout << "Most likely result: " << mostLikelyResult << std::endl;

}

std::string Game::getResultKey(int joeSetsWon, int sidSetsWon) {
    return std::to_string(joeSetsWon) + " : " + std::to_string(sidSetsWon);
}

Game::~Game()
{
}
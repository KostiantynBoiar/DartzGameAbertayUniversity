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


int Game::playerTurn(Player& player) {
    Dartz dartz;
    int remainingScore = player.getScore();
    int bufferScore = player.getScore();
    Dartz::Throw lastThrow;

    for (int i = 0; i < 3; i++) {
        int score = dartz.throwTreble(20, player.getAccuracy()); // Adjust the dartboard sequence
        std::cout << remainingScore << "|| " << player.getName() << std::endl;

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
        

    return -1; 
}


std::string Game::playGame(Player& player1, Player& player2)
{
    while (true) {
        // Joe's turn
        int result = playerTurn(player1);
        if (result == 0) {
            return "Joe"; // Joe won
        }
        else if (result == 1) {
            return "Sid"; // Sid won
        }

        // Sid's turn
        result = playerTurn(player2);
        if (result == 0) {
            return "Sid"; // Sid won
        }
        else if (result == 1) {
            return "Joe"; // Joe won
        }
    }
}


std::pair<int, int> Game::playSet() {
    int joeWins = 0;
    int sidWins = 0;
    for (int i = 0; i < 5; ++i) {
        std::string winner = playGame(this->player1, this->player2);
        if (winner == "Joe") {
            joeWins++;
        }
        else {
            sidWins++;
        }
    }
    return std::make_pair(joeWins, sidWins);
}

std::pair<int, int> Game::simulateFinal(int numSets) {
    srand(time(nullptr)); // Seed the random number generator

    int joeWins = 0;
    int sidWins = 0;

    for (int set = 0; set < numSets; ++set) {
        // Determine who throws first for the first game
        bool joeThrowsFirst = (rand() % 2 == 0);

        int joeSetsWon = 0;
        int sidSetsWon = 0;

        // Simulate the best of five games in the set
        for (int game = 0; game < 5; ++game) {
            // Simulate a game
            int joeScore = 501;
            int sidScore = 501;

            bool joeTurn = joeThrowsFirst;
            while (joeScore > 0 && sidScore > 0) {
                // Determine which player throws
                int result;
                if (joeTurn) {
                    result = playerTurn(player1);
                } else {
                    result = playerTurn(player2);
                }

                // Update the score
                if (joeTurn) {
                    joeScore -= result;
                } else {
                    sidScore -= result;
                }

                // Check for bust
                if (joeScore == 1 || sidScore == 1 || joeScore < 0 || sidScore < 0) {
                    // No points deducted for bust, the game continues
                } else if (joeScore == 0) {
                    ++joeSetsWon; // Joe wins the game
                    break;
                } else if (sidScore == 0) {
                    ++sidSetsWon; // Sid wins the game
                    break;
                }

                joeTurn = !joeTurn; // Switch turns
            }
        }

        // Update the total wins for Joe and Sid in the set
        if (joeSetsWon > sidSetsWon) {
            ++joeWins;
        } else {
            ++sidWins;
        }
    }

    return std::make_pair(joeWins, sidWins);
}


std::list<std::pair<int, int>> Game::resultsTable(std::pair<int, int> playSet) {
    std::list<std::pair<int, int>> results;

    // Generate the results table
    for (int i = 0; i < playSet.first + playSet.second; ++i) {
        if (i < playSet.first) {
            results.push_back(std::make_pair(2, 0)); // Joe wins the set
        }
        else {
            results.push_back(std::make_pair(0, 2)); // Sid wins the set
        }
    }

    return results;
}

void Game::drawResultsTable(const std::list<std::pair<int, int>>& results) {
    // Calculate the total number of sets played
    int totalSets = results.size();

    // Calculate the frequency of each outcome
    std::vector<int> frequency(8, 0); // We have 8 possible outcomes (0-7 sets won by Joe)
    for (const auto& setOutcome : results) {
        frequency[setOutcome.first]++;
    }

    // Output the results table in the specified format
    std::cout << "Joe : Sid Frequency" << std::endl;
    for (int i = 0; i <= 7; ++i) {
        double percent = (static_cast<double>(frequency[i]) / totalSets) * 100;
        std::cout << std::setw(2) << i << " : " << std::setw(2) << (7 - i) << " " << std::setw(4) << std::fixed << std::setprecision(0) << percent << "%" << std::endl;
    }
}

Game::~Game()
{
}

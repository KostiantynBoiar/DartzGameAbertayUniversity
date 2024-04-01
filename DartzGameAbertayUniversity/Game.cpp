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
    int bufferScore = remainingScore;
    Dartz::Throw lastThrow;
    int i = 0;

    while (i != 3) {

        int score = dartz.throwBull(player.getAccuracy()); // Adjust the dartboard sequence  
        lastThrow = Dartz::Throw::throwBullEnum;
        // Variable that will contain value of calculateThrow function in itself

        int calculatedThrow = calculateThrow(1, player);
        // If calculate throw value is suitable for player then he will throw a dart
        if (calculatedThrow != 0 && i == 2 && player.getScore() <= 20) {
            score = dartz.throwSingle(calculatedThrow, player.getAccuracy());
            i++;
        }

        //Variable that will contain map of the table
        std::unordered_map <Dartz::Throw, int> nextThrows = parseTable(remainingScore);

        //If variable is not empty then we will throw darts according to the most optimal strategy
        if (!nextThrows.empty() && i == 0) {
            for (auto nextThrow : nextThrows) {
                if (nextThrow.first == Dartz::Throw::throwSingleEnum) {
                    score = dartz.throwSingle(nextThrow.second, player.getAccuracy());
                }
                if (nextThrow.first == Dartz::Throw::throwDoubleEnum) {
                    score = dartz.throwDouble(nextThrow.second, player.getAccuracy());
                }
                if (nextThrow.first == Dartz::Throw::throwTrebleEnum) {
                    score = dartz.throwTreble(nextThrow.first, player.getAccuracy());
                }
                if (nextThrow.first == Dartz::Throw::throwBullEnum) {
                    score = dartz.throwBull(player.getAccuracy());
                }
                i++;
            }
        }
        // If nextThrows is empty then we will throw darts according to default strategy
        else {
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
                score = dartz.throwDouble(10, player.getAccuracy());
                break;
            case 40:
                score = dartz.throwDouble(20, player.getAccuracy());
                break;
            case 32:
                score = dartz.throwDouble(16, player.getAccuracy());
                break;
            case 60:
                score = dartz.throwTreble(20, player.getAccuracy());
                break;
            default:
                score = dartz.throwBull(player.getAccuracy());
                break;
            }
            i++;
        }
        // If last throw was not a throwDouble, throwThreble, throwBull we will set player score to the score buffer
        if (lastThrow == Dartz::Throw::throwSingleEnum && i == 3){
            return bufferScore;
        }
        if (bufferScore < 21 && i == 2) {
            if (bufferScore % 2 == 0) {
                score = dartz.throwDouble(bufferScore / 2, player.getAccuracy());
            }
            else score = dartz.throwDouble(bufferScore / 2 - 0.5, player.getAccuracy());
            i++;
        }

        if (remainingScore > 1) remainingScore -= score;
        if (remainingScore == 1) return -1;
        if (remainingScore < 0) remainingScore = bufferScore;
        if (remainingScore == 0) return 0;

    }
    player.setScore(remainingScore);
    i = 0;
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


std::unordered_map<Dartz::Throw, int> Game::parseTable(int remainingScore)
{
    std::unordered_map<Dartz::Throw, int> throwMap;

    // Check if the score is in the strategy table
    if (strategyTable.find(remainingScore) != strategyTable.end()) {
        std::string strategy = strategyTable[remainingScore];
        std::string throws[3];
        std::stringstream ss(strategy);
        for (int i = 0; i < 3; ++i) {
            if (std::getline(ss, throws[i], ',')) {
                char throwType = throws[i][0];
                std::string throwTarget = throws[i].substr(1);
                Dartz::Throw throwTypeValue;
                switch (throwType) {
                case 'S':
                    throwTypeValue = Dartz::Throw::throwSingleEnum;
                    break;
                case 'D':
                    throwTypeValue = Dartz::Throw::throwDoubleEnum;
                    break;
                case 'T':
                    throwTypeValue = Dartz::Throw::throwTrebleEnum;
                    break;
                case 'B':
                    throwTypeValue = Dartz::Throw::throwBullEnum;
                default:
                    continue;
                }
                int targetValue = std::stoi(throwTarget);
                throwMap[throwTypeValue] = targetValue;
            }
        }
    }


    return throwMap;
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

Dartz Game::getDartz()
{
    return this->dartz;
}

void Game::simulateFinal(int numSets) {
    srand(time(nullptr)); // Seed the random number generator

    // Initialize variables to track results
    std::map<std::string, double> result;
    int totalGames = 0;

    // Main loop for simulating matches
    for (int i = 0; i < numSets; i++) {
        // Reset sets won counters for each new set
        int joeSetsWon = 0;
        int sidSetsWon = 0;

        // Play sets until one player wins 7 sets
        while (joeSetsWon < 7 && sidSetsWon < 7) {
            bool turn = (rand() % 2 == 0); // Randomly choose starting player
            std::pair<int, int> res = playSet(turn);

            // Determine winner of the set and update counters
            if (res.first > res.second) {
                joeSetsWon++;
                player1.setIter(player1.getIter() + 1);
            }
            else {
                sidSetsWon++;
                player2.setIter(player2.getIter() + 1);

            }
        }

        // Record the outcome of the set
        std::string key = getResultKey(joeSetsWon, sidSetsWon);
        result[key]++;

        // Update total number of games played
        totalGames++;
    }

    // Output results
    std::cout << "Results:" << std::endl;
    std::cout << "Joe : Sid" << std::endl;
    for (const auto& pair : result) {
        std::cout << pair.first << " : " << (pair.second * 100) / totalGames << " %" << std::endl;
    }
    if (player1.getIter() > player2.getIter()) {
        std::cout << player1.getName() << " won!" << std::endl << "Total wins : " << player1.getIter() << std::endl;
    }
    else {
        std::cout << player2.getName() << " won!" << std::endl << "Total wins : " << player2.getIter() << std::endl;
    }
    // Find the most likely result
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


int Game::calculateThrow(int threbleD, Player& player) {
    const int maxRecursionDepth = 20;

    if (player.getScore() > 20) {
        return 0; // No need to calculate throw if score is already high
    }

    int bestThrow = 0;

    // Calculate the best throw based on the score difference
    for (int throwValue = 1; throwValue <= 20; ++throwValue) {
        int remainingScore = player.getScore() - dartz.throwSingle(throwValue, player.getAccuracy());
        if (remainingScore == 40 || remainingScore == 32 || remainingScore == 1) {
            return threbleD;
        }

    }

    return bestThrow;
}


Game::~Game()
{
}
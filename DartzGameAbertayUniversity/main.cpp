#include <iostream>
#include <iomanip>
#include "Game.h"
#include "Player.h"

int main() {
    // Seed the random number generator
    srand(time(nullptr));

    Player player1("Joe", 501);
    Player player2("Sid", 501);
    // Create a Game instance
    Dartz dartz;
    Game game(player1, player2, dartz);

    // Simulate a final between Joe and Sid with 10 sets
    //std::pair<int, int> finalResult = game.simulateFinal(100);

    game.playerTurn(player1);
    /*
    // Generate the results table for the final
    std::list<std::pair<int, int>> results = game.resultsTable(finalResult);

    // Output the results table
    game.drawResultsTable(results);
    */

    return 0;
}
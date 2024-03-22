#include <iostream>
#include <iomanip>
#include "Game.h"
#include "Player.h"

int main() {
    // Seed the random number generator
    srand(time(nullptr));

    Player player1("Joe", 501, 90);
    Player player2("Sid", 501, 90);
    // Create a Game instance
    int countOfSimulation = 100;
    Dartz dartz;
    Game game(player1, player2, dartz);
    std::cout << "Count of simulation: " << countOfSimulation << std::endl;
    std::cout << "Joe accuracy: " << player1.getAccuracy() << std::endl << "Sid accuracy: " << player2.getAccuracy() << std::endl;

   
      // Simulate a final between Joe and Sid with 10 sets
      game.simulateFinal(countOfSimulation);


  

    return 0;
}
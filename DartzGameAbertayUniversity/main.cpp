/*
 Author: Kostiantyn Boiar 2303596 
*/

#include <iostream>
#include <iomanip>
#include "Game.h"
#include "Player.h"

int main() {

    Player player1("Joe", 501, 90);
    Player player2("Sid", 501, 90);
    // Create a Game instance
    int countOfSimulation;
    std::cout << "Input count of simulation: ";
    std::cin >> countOfSimulation;
    Dartz dartz;
    Game game(player1, player2, dartz);
    std::cout << "Count of simulation: " << countOfSimulation << std::endl;
    std::cout << "Joe accuracy: " << player1.getAccuracy() << std::endl << "Sid accuracy: " << player2.getAccuracy() << std::endl;

   
      // Simulate a final between Joe and Sid with 10 sets
    game.simulateFinal(countOfSimulation);
    system("pause");

  

    return 0;
}
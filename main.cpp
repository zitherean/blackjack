#include "game.h"

#include <iostream>

int main()
{
    Game game;
    game.start();

    if (!game.isRunning()) {
        return 0;
    }

    while (true) {
        game.playRound();
        if (!game.isEnoughPlayers()) {
            break; // Exit the loop if there are not enough players
        }

        std::cout << ">>> Do you want to play another round? (y/n): ";
        char choice;
        std::cin >> choice;
        if (choice != 'y' && choice != 'Y') {
            break; // Exit the loop if the user does not want to continue
        }
    }

    game.end();

    return 0;
}
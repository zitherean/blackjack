#ifndef PLAYER_UTILS_H
#define PLAYER_UTILS_H

#include "player.h"

#include <iostream>

class PlayerUtils {
    public:
        void createPlayers(std::vector<Player>& players);
        void takeBets(std::vector<Player>& players);
        void display(std::vector<Player>& players);
        void remove(std::vector<Player>& players);

    private:
        bool isValidBalance(int balance);
        int numPlayers = 0;
        const int MAX_PLAYERS = 7; // Maximum number of players allowed
        const int MIN_PLAYERS = 1; // Minimum number of players allowed
        const int STARTING_BALANCE = 1000; // Starting balance for each player};
};

#endif
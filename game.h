#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "deck.h"
#include "hand.h"
#include "player_utils.h"

class Game {
    public:
        void start();
        void playRound();
        bool isRunning() const;
        bool isEnoughPlayers() const;
        void end();
        void testSplit(); // For testing split functionality
    
    private:
        std::vector<Player> players;
        Player dealer = Player("Dealer", 0); // Initialize the dealer with a name and a balance of $0. The balance does not matter for the dealer.
        PlayerUtils playerUtils;
        Deck deck;
        void playerTurn();
        void dealerTurn();
        void determineWinner();
        void initializeGame();
        void handleSplit(Player& player); // Handle split logic for a player

        bool isActive = false; // Flag to check if the game is active
        const int DEALER_HIT_THRESHOLD = 17; // Dealer must hit until reaching this value
        const int BLACKJACK_MULTIPLIER = 3; // Multiplier for winning a blackjack
        const int WIN_MULTIPLIER = 2; // Multiplier for winning a regular hand
};

#endif
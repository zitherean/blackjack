#ifndef PLAYER_H
#define PLAYER_H

#include "hand.h"

#include <string>

class Player{
    public:
        Player(std::string name, int balance);
        std::string getName() const;
        int getBalance() const;
        void adjustBalance(int amount);
        bool placeBet(int amount);
        bool doubleDown();
        void winBet(int multiplier); // Multiplier for winning a bet
        void loseBet();
        void pushBet();
        int getCurrentBet() const;
        void clearBet();

        Hand& getHand();
        void clearHand();

        std::vector<Hand> splitHands;
        std::vector<int> splitBets;
        int hasSplit = false;

    private:
        std::string name_;
        int balance_;
        int currentBet = 0; // Current bet amount
        Hand hand;
};

#endif
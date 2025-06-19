#ifndef HAND_H
#define HAND_H

#include "card.h"

#include <vector>

class Hand {
    public:
        void addCard(const Card& card);
        Card getCard(int index) const; 
        bool isBlackjack() const;
        bool isBusted() const;
        bool isSplit() const;
        int getTotalValue() const;
        void clear();
        int size() const;
        std::string display() const;
        std::string halfDisplay() const;

    private:
        std::vector<Card> cards;
        static const int BLACKJACK_VALUE = 21; // Value for blackjack
        static const int ACE_ADJUSTMENT = 10; // Adjustment from 11 to 1 for Ace when busting
};

#endif
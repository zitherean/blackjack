#ifndef DECK_H
#define DECK_H

#include "card.h"

#include <vector>

class Deck{
    public:
        Deck();
        void shuffle();
        Card dealCard();
        void reset();
        bool isEmpty() const;
        int size() const;

    private:
        std::vector<Card> cards;
        size_t currentIndex;
};

#endif
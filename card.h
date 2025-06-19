#ifndef CARD_H
#define CARD_H

#include <string>

class Card {
    public:
        enum Suit {HEARTS, DIAMONDS, CLUBS, SPADES};
        enum Rank {TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE};
        Card(Rank rank, Suit suit);
        Suit getSuit() const;
        Rank getRank() const;
        int getValue() const;
        std::string toString() const;
        bool isEqualRank(const Card& other) const;

    private:
        Suit suit_;
        Rank rank_;
        static const int FACE_CARD_VALUE = 10; // Value for face cards (Jack, Queen, King)
        static const int ACE_VALUE = 11; // Value for Ace
    };

#endif
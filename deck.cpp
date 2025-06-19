#include "deck.h"

#include <stdexcept>
#include <algorithm>
#include <random>

// Deck constructor initializes the deck
Deck::Deck()
{
    reset();
}

// Function to shuffle the deck of cards
void Deck::shuffle()
{
    std::random_device rd; // Obtain a random number from hardware
    std::mt19937 eng(rd()); // Seed the generator
    std::shuffle(cards.begin(), cards.end(), eng); // Shuffle the deck
}

// Function to deal a card from the deck
Card Deck::dealCard()
{
    if (isEmpty()) {
        throw std::out_of_range("No more cards to deal from the deck.");
    }

    Card c = cards.at(currentIndex);
    currentIndex++;
    return c;
}

// Function to reset the deck to its initial state
void Deck::reset()
{
    cards.clear();

    // Populate the deck with cards
    for (int suit = Card::HEARTS; suit <= Card::SPADES; ++suit) {
        for (int rank = Card::TWO; rank <= Card::ACE; ++rank) {
            cards.emplace_back(static_cast<Card::Rank>(rank), static_cast<Card::Suit>(suit));
        }
    }

    currentIndex = 0; // Reset the current index to the start of the deck
}

// Function to check if the deck is empty
bool Deck::isEmpty() const
{
    return currentIndex >= cards.size();
}

// Function to get the size of the deck
int Deck::size() const
{
    return cards.size() - currentIndex;
}
#include "hand.h"

#include <stdexcept>

// Function to add a card to the hand
void Hand::addCard(const Card& card)
{
    cards.push_back(card);
}

// Function to get a card by index
Card Hand::getCard(int index) const
{
    if (index < 0 || index >= static_cast<int>(cards.size())) {
        throw std::out_of_range("Index out of range for card retrieval.");
    }
    return cards.at(index);
}

// Function to check blackjack
bool Hand::isBlackjack() const
{
    return cards.size() == 2 && getTotalValue() == BLACKJACK_VALUE;
}

//Function to check bust
bool Hand::isBusted() const
{
    return getTotalValue() > BLACKJACK_VALUE;
}

// Function to check if the hand can be split
bool Hand::isSplit() const
{
    if (cards.size() != 2) {
        return false; // Cannot split if not exactly two cards
    }
    return cards.at(0).isEqualRank(cards.at(1)); // Can split if both cards have the same rank
}

// Function to get the total value of the hand
int Hand::getTotalValue() const
{
    int total = 0;
    int aceCount = 0;

    for (size_t i = 0; i < cards.size(); i++) {
        total += cards.at(i).getValue();
        if (cards.at(i).getRank() == Card::ACE) {
            aceCount++; 
        }
    }

    while(total > BLACKJACK_VALUE && aceCount > 0) {
        total -= ACE_ADJUSTMENT;
        aceCount--;
    }

    return total;
}

// Function to clear the hand
void Hand::clear()
{
    cards.clear();
}

// Function to get the size of the hand
int Hand::size() const
{
    return cards.size();
}

// Function to convert the hand to a string representation
std::string Hand::display() const
{
    std::string handStr;
    for (size_t i = 0; i < cards.size(); i++) {
        handStr += cards.at(i).toString();
        if (i < cards.size() - 1) {
            handStr += ", "; // Add a comma between cards
        }
    }
    return handStr;
}

// Function to display the dealer's hand, showing only the first card
std::string Hand::halfDisplay() const
{   
    std::string dealerHandStr = cards.at(0).toString() + "," + " [Hidden]";
    return dealerHandStr;
}
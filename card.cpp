#include "card.h"

// Constructor for Card class
Card::Card(Rank rank, Suit suit)
{
    suit_ = suit;
    rank_ = rank;
}

// Suit and Rank getters
Card::Suit Card::getSuit() const
{
    return suit_;
}

Card::Rank Card::getRank() const
{
    return rank_;
}

// Function to get the value of the card based on its rank
int Card::getValue() const
{
    if (rank_ >= TWO && rank_ <= TEN) {
        return rank_;
    }
    else if (rank_ == JACK || rank_ == QUEEN || rank_ == KING) {
        return FACE_CARD_VALUE; // Face cards (Jack, Queen, King) are worth 10 points
    } 
    else if (rank_ == ACE) {
        return ACE_VALUE; // Ace is worth 11 points. Logic for adjusting Ace value is handled in Hand class
    }

    return 0; // Default case, should not happen
}

// Function to check if two cards are equal based on their rank
bool Card::isEqualRank(const Card& other) const
{
    return rank_ == other.rank_;
}

// Function to convert the card to a string representation
std::string Card::toString() const
{
    std::string suitStr;
    switch (suit_) {
        case HEARTS:   
            suitStr = "♥"; 
            break;
        case DIAMONDS: 
            suitStr = "♦"; 
            break;
        case CLUBS:    
            suitStr = "♣"; 
            break;
        case SPADES:   
            suitStr = "♠"; 
            break;
        default:
            suitStr = "Unknown Suit"; // Fallback for unknown suit
            break;
    }

    std::string rankStr;
    switch (rank_) {
        case TWO:   
            rankStr = "2"; 
            break;
        case THREE: 
            rankStr = "3"; 
            break;
        case FOUR:  
            rankStr = "4"; 
            break;
        case FIVE:  
            rankStr = "5"; 
            break;
        case SIX:   
            rankStr = "6"; 
            break;
        case SEVEN: 
            rankStr = "7"; 
            break;
        case EIGHT: 
            rankStr = "8"; 
            break;
        case NINE:  
            rankStr = "9"; 
            break;
        case TEN:   
            rankStr = "10"; 
            break;
        case JACK:  
            rankStr = "J"; 
            break;
        case QUEEN: 
            rankStr = "Q"; 
            break;
        case KING:  
            rankStr = "K"; 
            break;
        case ACE:   
            rankStr = "A"; 
            break;
        default:
            rankStr = "Unknown Rank"; // Fallback for unknown rank
            break;
    }

    return rankStr + " of " + suitStr;
}
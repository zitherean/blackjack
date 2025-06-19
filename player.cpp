#include "player.h"

// Constructor for Player class
Player::Player(std::string name, int balance)
{
    name_ = name;
    balance_ = balance;
}

// Function to get the player's name
std::string Player::getName() const
{
    return name_;
}

// Function to get the player's balance
int Player::getBalance() const
{
    return balance_;
}

// Function to adjust the player's balance
void Player::adjustBalance(int amount)
{
    balance_ += amount;
}

// Function to place a bet
bool Player::placeBet(int amount)
{
    if (amount <= balance_ && amount > 0) {
        balance_ -= amount;
        currentBet = amount;
        return true; // Bet placed successfully
    }
    return false; // Bet failed due to insufficient balance or invalid amount
}

// Function to double down on the current bet
bool Player::doubleDown()
{
    if (currentBet > 0 && balance_ >= currentBet) {
        balance_ -= currentBet;
        currentBet *= 2; // Double the current bet
        return true; // Double down successful
    }
    return false; // Double down failed due to insufficient balance or no current bet
}

// Function to win a bet
void Player::winBet(int multiplier)
{
    balance_ += currentBet * multiplier; // Win the bet, so add the bet amount multiplied by the multiplier to the balance
    currentBet = 0;
}

// Function to lose a bet
void Player::loseBet()
{
    // Lose the bet, no need to adjust balance as it was already done in placeBet
    currentBet = 0; 
}

// Function to push a bet (tie)
void Player::pushBet()
{
    balance_ += currentBet; // Return the bet amount to the player
    currentBet = 0;
}

// Function to get the current bet amount
int Player::getCurrentBet() const
{
    return currentBet;
}

// Function to clear the current bet
void Player::clearBet()
{
    currentBet = 0;
}

// Function to get the player's hand
Hand& Player::getHand()
{
    return hand;
}

// Function to clear the player's hand
void Player::clearHand()
{
    hand.clear(); 
    splitBets.clear();
    splitHands.clear(); 
    hasSplit = false; 
}
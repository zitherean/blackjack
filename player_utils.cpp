#include "player_utils.h"

// Function to create players and initialize their names and balances
void PlayerUtils::createPlayers(std::vector<Player>& players)
{
    std::cout << "\n>>> How many players are in the game? Enter a number between " << MIN_PLAYERS << " and " << MAX_PLAYERS << ": ";
    while(std::cin >> numPlayers) {
        if (numPlayers < MIN_PLAYERS || numPlayers > MAX_PLAYERS) {
            std::cout << ">>> Invalid number of players. Please enter a number between " << MIN_PLAYERS << " and " << MAX_PLAYERS << ": ";
            continue; // Prompt again if the input is invalid
        }
        break; // Exit the loop if a valid number of players is entered
    }

    std::cin.ignore(); // Clear the input buffer before reading a line

    players.reserve(numPlayers); // Resize the vector to hold the specified number of players
    for (int i = 0; i < numPlayers; i++) {
        std::string playerName;
        std::cout << "\n>>> Enter the name of player " << i + 1 << ": ";
        std::getline(std::cin, playerName); 
        players.push_back(Player(playerName, STARTING_BALANCE)); // Initialize each player with a name and a starting balance of $1000
        std::cout << ">>> Welcome " << playerName << "! You have a starting balance of $" << STARTING_BALANCE << "." << std::endl;
    }
}

// Function to take bets from each player
void PlayerUtils::takeBets(std::vector<Player>& players)
{
    for (size_t i = 0; i < players.size(); i++) {
        Player& player = players.at(i);

        std::cout << "\n>>> " << player.getName() << ", you have a balance of $" << player.getBalance() << ". How much would you like to bet? ";
        
        int betAmount = 0;
        while (std::cin >> betAmount) {
            if (betAmount <= 0 || betAmount > player.getBalance()) {
                std::cout << ">>> Invalid bet amount. Please enter a valid amount: ";
                continue; // Prompt again if the input is invalid
            } 
            else {
                break; // Exit the loop if a valid bet amount is entered
            }
        }

        if (player.placeBet(betAmount)) {
            std::cout << ">>> " << player.getName() << " has placed a bet of $" << betAmount << "." << std::endl;
        } else {
            std::cout << ">>> Bet placement failed for " << player.getName() << "." << std::endl;
        }
    }
    std::cout << "\n>>> All bets have been placed.\n" << std::endl;
}

// Function to display the current players in the game, excluding the dealer
void PlayerUtils::display(std::vector<Player>& players)
{
    std::cout << "\n>>> Current Players in the Game:" << std::endl;
    for (size_t i = 0; i < players.size(); i++) {
        std::cout << ">>> Player Name: " << players.at(i).getName() << ", Balance: $" << players.at(i).getBalance() << std::endl;
    }
}

// Function to remove players with invalid balances
void PlayerUtils::remove(std::vector<Player>& players)
{
    for (size_t i = 0; i < players.size(); i++) {
        if (!isValidBalance(players.at(i).getBalance())) {
            std::cout << "\n>>> " << players.at(i).getName() << " has an invalid balance of $" << players.at(i).getBalance() << ". You will be removed from the game." << std::endl;
            players.erase(players.begin() + i);
            i--; // Adjust index after removal
        }
    }
}

// Helper function to check if a balance is valid
bool PlayerUtils::isValidBalance(int balance)
{
    return balance > 0; // A valid can only be positive
}
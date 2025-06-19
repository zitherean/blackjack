#include "game.h"

#include <iostream>
#include <unistd.h>

// Function to start the game and initialize the players and deck
void Game::start() 
{
    initializeGame();
}

// Function to play a round of blackjack
void Game::playRound()
{
    // Clear player's and dealer's hand for a new round
    for (size_t i = 0; i < players.size(); i++) {
        Player& player = players.at(i);
        player.clearHand();
    }
    dealer.clearHand(); 

    // Take bets from players
    playerUtils.takeBets(players);

    std::cout << ">>> Dealing cards..." << std::endl;
    sleep(2); // Simulate a delay for dealing cards

    // Deal initial cards to players and dealer
    for (size_t i = 0; i < players.size(); i++) {
        Player& player = players.at(i);
        player.getHand().addCard(deck.dealCard());
        player.getHand().addCard(deck.dealCard());
        std::cout << ">>> " << player.getName() << "'s hand: " << player.getHand().display() << std::endl;
        sleep(1);
    }

    dealer.getHand().addCard(deck.dealCard());
    dealer.getHand().addCard(deck.dealCard());
    std::cout << ">>> Dealer's hand: " << dealer.getHand().halfDisplay() << std::endl;
    sleep(2);

    // Player's turn
    playerTurn();

    // Dealer's turn
    dealerTurn();

    // Determine the winner
    determineWinner();

    deck.reset();
    deck.shuffle();
    playerUtils.remove(players); // Remove players with invalid balances
    playerUtils.display(players);
    std::cout << "\n>>> End of the round." << std::endl;
    sleep(2);
}

// Function to check if the game is running
bool Game::isRunning() const
{
    return isActive;
}

// Function to check if there are enough players to continue the game
bool Game::isEnoughPlayers() const
{
    if (players.size() < 2) {
        std::cout << ">>> Not enough players to start the game. At least one player and one dealer are required." << std::endl;
        return false; // Not enough players to start the game
    }
    return true; // Enough players to start the game
}

// Function to end the game
void Game::end()
{
    std::cout << "\n>>> Thank you for playing! The game has ended." << std::endl;
    sleep(2);
}

// Helper function to initialize the game by creating players and shuffling the deck
void Game::initializeGame()
{
    std::cout << ">>> Welcome to the popular card game Blackjack! "
              << "A maximum of 7 (seven) players are allowed to play at once. "
              << "The game will start with each player having a balance of $1000.\n" << std::endl;
    std::cout << ">>> Are you ready to start? (y/n): ";

    char startGame;
    std::cin >> startGame;
    if (startGame != 'y' && startGame != 'Y') {
        std::cout << "\n>>> Exiting the game. Goodbye!" << std::endl;
        isActive = false; // Set the game as inactive
        sleep(2);
        return; // Exit if the user does not want to start the game
    }

    playerUtils.createPlayers(players);
    deck.shuffle();	
    isActive = true; // Set the game as active
}

// Function to handle the player's turn
void Game::playerTurn()
{
    for (size_t i = 0; i < players.size(); i++) {
        sleep(1); // Simulate a delay before starting the player's turn
        Player& player = players.at(i);
        std::cout << "\n>>> " << player.getName() << "'s turn." << std::endl;
        sleep(1);

        while (true) {
            std::cout << ">>> Current hand: " << player.getHand().display() << std::endl;
            std::cout << ">>> Total value: " << player.getHand().getTotalValue() << std::endl;

            if (player.getHand().isBlackjack()) {
                std::cout << ">>> " << player.getName() << " has a blackjack!" << std::endl;
                sleep(1);
                break; // Player has blackjack, end their turn
            }

            if (player.getHand().isBusted()) {
                std::cout << ">>> " << player.getName() << " busts!" << std::endl;
                sleep(1);
                break; // Player is busted, end their turn
            }

            std::cout << ">>> Choose an action: (h)it, (s)tand, (d)ouble down, s(p)lit: ";
            char action;
            std::cin >> action;

            if (action == 'h' || action == 'H') {
                player.getHand().addCard(deck.dealCard());
                std::cout << ">>> " << player.getName() << " hits." << std::endl;
                sleep(1);
            } else if (action == 's' || action == 'S') {
                std::cout << ">>> " << player.getName() << " stands." << std::endl;
                sleep(1);
                break; // Player stands, end their turn
            } else if (action == 'd' || action == 'D') {
                if (player.getBalance() < player.getCurrentBet()) {
                    std::cout << ">>> Insufficient balance to double down." << std::endl;
                } else if (player.getHand().isBlackjack()) {
                    std::cout << ">>> Cannot double down, player already has a blackjack." << std::endl;
                } else if (player.getHand().size() > 2) {
                    std::cout << ">>> Cannot double down, more than two cards in hand." << std::endl;
                } else {
                    if (player.doubleDown()) {
                        player.getHand().addCard(deck.dealCard()); // Deal one more card
                        std::cout << ">>> " << player.getName() << " doubles down." << std::endl;
                        std::cout << ">>> " << player.getName() << "'s new hand: " << player.getHand().display() << std::endl;
                        std::cout << ">>> Total value: " << player.getHand().getTotalValue() << std::endl;
                        sleep(1);
                    }
                    break; // End the turn after doubling down
                }
            } else if (action == 'p' || action == 'P') {
                if (player.getHand().size() != 2) {
                    std::cout << ">>> Cannot split, you must have exactly two cards to split." << std::endl;
                } else if (player.getBalance() < player.getCurrentBet()) {
                    std::cout << ">>> Insufficient balance to split." << std::endl;
                } else {
                    if (player.getHand().isSplit()) {
                        handleSplit(player);
                        break;
                    }
                    else {
                        std::cout << ">>> Cannot split, the two cards must have the same rank." << std::endl;
                    }
                }
            } else {
                std::cout << ">>> Invalid action. Please choose again." << std::endl;
            }
        }
    }
}

// Function to handle split logic for a player
void Game::handleSplit(Player& player) 
{
    Hand original = player.getHand();
    Card first = original.getCard(0);
    Card second = original.getCard(1);

    if (player.placeBet(player.getCurrentBet())) {
        player.clearHand(); // Clear original hand
        player.hasSplit = true;

        Hand hand1, hand2;
        hand1.addCard(first);
        hand1.addCard(deck.dealCard());

        hand2.addCard(second);
        hand2.addCard(deck.dealCard());

        player.splitHands.push_back(hand1);
        player.splitHands.push_back(hand2);
        player.splitBets.push_back(player.getCurrentBet());
        player.splitBets.push_back(player.getCurrentBet());

        std::cout << ">>> " << player.getName() << " splits their hand." << std::endl;

        // Now play both split hands
        for (size_t h = 0; h < player.splitHands.size(); ++h) {
            std::cout << "\n>>> Playing split hand " << (h + 1) << " for " << player.getName() << std::endl;

            while (true) {
                Hand& currentHand = player.splitHands.at(h);
                std::cout << ">>> Current hand: " << currentHand.display() << std::endl;
                std::cout << ">>> Total value: " << currentHand.getTotalValue() << std::endl;

                if (currentHand.isBlackjack()) {
                    std::cout << ">>> Blackjack!" << std::endl;
                    sleep(1);
                    break;
                }

                if (currentHand.isBusted()) {
                    std::cout << ">>> Busted!" << std::endl;
                    sleep(1);
                    break;
                }

                std::cout << ">>> Choose an action for hand " << (h + 1) << ": (h)it or (s)tand: ";
                char subAction;
                std::cin >> subAction;

                if (subAction == 'h' || subAction == 'H') {
                    currentHand.addCard(deck.dealCard());
                    sleep(1);
                } else if (subAction == 's' || subAction == 'S') {
                    sleep(1);
                    break;
                } else {
                    std::cout << ">>> Invalid input." << std::endl;
                }
            }
        }
    }
}

// Function to handle the dealer's turn
void Game::dealerTurn()
{
    sleep(2); // Simulate a delay before starting the dealer's turn
    std::cout << "\n>>> " << dealer.getName() << "'s turn." << std::endl;
    std::cout << ">>> " << dealer.getName() << "'s hand: " << dealer.getHand().display() << std::endl;
    std::cout << ">>> Total value: " << dealer.getHand().getTotalValue() << std::endl;

    while (dealer.getHand().getTotalValue() < DEALER_HIT_THRESHOLD) {
        std::cout << ">>> " << dealer.getName() << " hits." << std::endl;
        dealer.getHand().addCard(deck.dealCard());
        std::cout << ">>> " << dealer.getName() << "'s hand: " << dealer.getHand().display() << std::endl;
        std::cout << ">>> Total value: " << dealer.getHand().getTotalValue() << std::endl;
        sleep(2);
    }

    if (dealer.getHand().isBusted()) {
        std::cout << ">>> " << dealer.getName() << " busts!" << std::endl;
    } else {
        std::cout << ">>> " << dealer.getName() << " stands with a total value of " << dealer.getHand().getTotalValue() << "." << std::endl;
    }
}

// Helper function to determine the winner of the game
void Game::determineWinner()
{
    std::cout << "\n>>> Determining the winner(s)..." << std::endl;
    sleep(2); // Simulate a delay before determining the winner
    for (size_t i = 0; i < players.size(); i++) {
        Player& player = players.at(i);
        int playerTotal = player.getHand().getTotalValue();
        int dealerTotal = dealer.getHand().getTotalValue();

        if (!player.hasSplit) {
            if (dealer.getHand().isBlackjack() && player.getHand().isBlackjack()) {
                player.pushBet();
                std::cout << ">>> " << player.getName() << " pushes against the dealer's blackjack." << std::endl;
                sleep(1);
            } else if (dealer.getHand().isBlackjack()) {
                player.loseBet();
                std::cout << ">>> " << player.getName() << " loses against the dealer's blackjack." << std::endl;
                sleep(1);
            } else if (player.getHand().isBlackjack()) {  
                player.winBet(BLACKJACK_MULTIPLIER);
                std::cout << ">>> " << player.getName() << " wins with a blackjack!" << std::endl;
                sleep(1);
            } else if (player.getHand().isBusted()) {
                player.loseBet();
                std::cout << ">>> " << player.getName() << " loses." << std::endl;
                sleep(1);
            } else if (dealer.getHand().isBusted() || playerTotal > dealerTotal) {
                player.winBet(WIN_MULTIPLIER);
                std::cout << ">>> " << player.getName() << " wins!" << std::endl;
                sleep(1);
            } else if (playerTotal < dealerTotal) {
                player.loseBet();
                std::cout << ">>> " << player.getName() << " loses." << std::endl;
                sleep(1);
            } else {
                player.pushBet();
                std::cout << ">>> " << player.getName() << " pushes." << std::endl;
                sleep(1);
            }
        } else {

            for (size_t j = 0; j < player.splitHands.size(); ++j) {
                int playerTotal = player.splitHands.at(j).getTotalValue();
                int dealerTotal = dealer.getHand().getTotalValue();
                int bet = player.splitBets.at(j);

                std::cout << ">>> Evaluating split hand " << (j + 1) << " of " << player.getName() << std::endl;
                sleep(2);

                if (player.splitHands.at(j).isBusted()) {
                    std::cout << ">>> Busted. Lost $" << bet << std::endl;
                    sleep(1);
                    // No balance adjustment needed; already paid
                } else if (dealer.getHand().isBusted() || playerTotal > dealerTotal) {
                    player.adjustBalance(bet * WIN_MULTIPLIER); // Won, return original + winnings
                    std::cout << ">>> Win! Gained $" << bet * WIN_MULTIPLIER << std::endl;
                    sleep(1);
                } else if (playerTotal < dealerTotal) {
                    player.adjustBalance(0); // Lost, no balance adjustment needed
                    std::cout << ">>> Loss." << std::endl;
                    sleep(1);
                } else {
                    player.adjustBalance(bet); // Push: return bet
                    std::cout << ">>> Push. Bet returned." << std::endl;
                    sleep(1);
                }
            }
        }
    }
}

// Function to test the split functionality
void Game::testSplit()
{
    players.push_back(Player("Player1", 1000)); // Add a test player

    players.at(0).placeBet(100);
    Hand hand;
    hand.addCard(Card(Card::EIGHT, Card::HEARTS));
    hand.addCard(Card(Card::EIGHT, Card::DIAMONDS));
    players.at(0).getHand() = hand; // Set the player's hand to the test hand
    
    std::cout << ">>> Forcing split test..." << std::endl;
    playerTurn();  // Manually call it

    dealer.getHand().addCard(Card(Card::TEN, Card::CLUBS)); // Let dealer draw at least one card
    dealer.getHand().addCard(Card(Card::NINE, Card::SPADES)); // Add another card to dealer's hand
    dealerTurn(); // Dealer plays their turn

    determineWinner();

    std::cout << ">>> " << players.at(0).getName() << "'s balance is: " << players.at(0).getBalance() << std::endl;

    std::cout << ">>> Split test completed.\n" << std::endl;
}
# 🃏 Blackjack

Welcome to a classic game of **Blackjack**, playable entirely in your terminal! This C++ implementation supports up to 7 players in a single local session and brings key gameplay mechanics like **hit**, **stand**, **double down**, and **split** into a text-based interface.

---

## ✨ Features

-  **Text-Based Interface** – Intuitive terminal experience, no GUI required.
-  **Multiplayer Support** – Play with up to 7 players in one session.
-  **Realistic Blackjack Logic** – Includes core actions and dealer AI.

---

## 🚀 How to Run

1. **Clone** or download the project to your machine.
2. Open the folder in your preferred code editor.
3. Open a terminal and **navigate** to the project directory.
4. **Compile** all the source files:

   ```bash
   g++ -Wall player.cpp card.cpp deck.cpp hand.cpp game.cpp player_utils.cpp main.cpp
  
5. **Run** the game:
   ```bash
   ./a.out

---

## 📝 Notes
- Some features (like surrender) are not yet implemented.
- Simulated delays (sleep()) are used for more realistic pacing.
- Local play only – no networking or online multiplayer.
- Deck is reshuffled each round to keep things simple and fair.
   

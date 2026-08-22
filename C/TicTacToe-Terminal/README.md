# Tic-Tac-Toe (C Implementation)

A classic, terminal-based Tic-Tac-Toe game developed in C. This project features a robust logic system supporting both local multiplayer and three distinct single-player AI difficulty levels.

## 🚀 Features

* Terminal UI: Clean and intuitive command-line interface with a visual board grid.
* Local Multiplayer: Play against a friend on the same machine.
* Singleplayer AI: Challenge yourself against a computer with three difficulty modes:
    * Easy: The bot makes random moves across the board.
    * Normal: The bot attempts to win or block the player's immediate winning moves.
    * Hard: Implements the Minimax Algorithm, making the computer virtually unbeatable.
* Dynamic Gameplay: Includes random player sorting to decide who starts the match.
* Memory Management: Utilizes dynamic memory allocation for game state handling.

## 🛠️ Technical Implementation

The project is structured into modular components to ensure clean, maintainable code:

* main.c: The entry point that manages the primary game loop and memory lifecycle.
* common.c/h: Contains the core engine, including board rendering, input decoding, and win-condition checking.
* multiplayer.c/h: Handles the logic for Human vs. Human matches.
* singleplayer.c/h: Contains the AI logic, ranging from simple random number generation to recursive pathfinding (Minimax).

## 🎮 How to Play

1. Compile the project:
   Use gcc (or your preferred C compiler) to link all files:
   gcc main.c common.c multiplayer.c singleplayer.c -o tictactoe -lm

2. Run the game:
   ./tictactoe

3. Navigate the Menu:
   * Choose 1 for Local Multiplayer.
   * Choose 2 for Singleplayer (then select difficulty).
   * Choose 3 for a quick tutorial on coordinate inputs (1-9).

## 🧠 AI Logic: The Hard Mode
The "Hard" difficulty utilizes the Minimax Algorithm, a backtracking algorithm used in decision-making and game theory. It explores all possible future moves to find the optimal strategy, ensuring that if the player plays perfectly, the result will always be a draw.

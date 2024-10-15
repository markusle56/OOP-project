#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Board.h"
#include <vector>
#include <iostream>

// Main control class for the chess game
class Game {
    private:
        Board board; // Game board
        bool isWhiteTurn; // Tracks white's turn
        bool gameOver; // Tracks if the game is over
        sf::RenderWindow window; // Main game window
        std::vector<Move> possibleMoves; // Possible moves for selected piece
        Piece * selectedPiece; // Currently selected piece
        sf::RenderWindow subWindow; // Promotion window
        bool subWindowOpen; // Is promotion window open
        int stage; // Game stage tracker
    public:
        Game(); // Constructor
        ~Game(); // Destructor
        void init(); // Initialize game
        void run(); // Main game loop
        void render(); // Render objects
        void handleInput(); // Handle user input
        void update(); // Update game state
        void drawPromote(sf::RenderWindow & subWindow); // Draw promotion window
        void resetGame(); // Reset game state
        void display(int x, int y); // Display the state of game
};

#endif
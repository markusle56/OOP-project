#ifndef MOVE_H
#define MOVE_H

#include "Piece.h"
#include <SFML/Graphics.hpp>

// Class to represent a chess move
class Move {
    private:
        Piece* captured_piece; // Pointer to the captured piece, if any
    
    public:
        Move(int startX, int startY, int endX, int endY, Piece* captured); // Constructor

        void execute(Board& board); // Executes the move on the given board
        bool isTargeted(Piece *piece); // Checks if the move targets the given piece
        void draw(sf::RenderWindow &window); // Draws the move highlight on the window

        int startX, startY; // Starting position of the move
        int endX, endY; // Ending position of the move
};

#endif

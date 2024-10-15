#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

// Rook class inherits from Piece
class Rook : public Piece {
    private:
        bool firstMove; // Tracks if Rook has moved
    public:
        Rook(bool isWhite, int x, int y); // Constructor
        void draw(sf::RenderWindow &window); // Draw the Rook
        virtual std::vector<Move> getPossibleMoves(Board& board); // Get possible moves
        bool isSwappable(bool isWhite); // Check if swappable
        bool getFirstMove(); // Check if it's the first move
        void doFirstMove(); // Mark that the first move has been made
};

#endif
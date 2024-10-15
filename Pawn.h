#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

// Pawn class inherits from Piece
class Pawn : public Piece {
    private:
        bool firstMove; // Tracks if it's the pawn's first move
    public:
        Pawn(bool isWhite, int x, int y);  // Constructor
        virtual std::vector<Move> getPossibleMoves(Board& board); // Get possible moves
        void draw(sf::RenderWindow& window); // Draw the Pawn
        bool isSwappable(bool isWhite); // Check if swappable
        void doFirstMove(); // Mark that the first move has been made
};

#endif
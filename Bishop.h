#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

// Bishop class inherits from Piece
class Bishop : public Piece {
    public:
        Bishop(bool isWhite, int x, int y); // Constructor
        void draw(sf::RenderWindow &window); // Draw the Bishop
        virtual std::vector<Move> getPossibleMoves(Board& board); // Get possible moves
        bool isSwappable(bool isWhite); // Check if swappable
};

#endif
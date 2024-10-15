#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

// Knight class inherits from Piece
class Knight : public Piece {
    public:
        Knight(bool isWhite, int x, int y); // Constructor
        void draw(sf::RenderWindow &window); // Draw the Knight
        virtual std::vector<Move> getPossibleMoves(Board& board); // Get possible moves
        bool isSwappable(bool isWhite); // Check if swappable
};

#endif
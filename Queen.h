#ifndef QUEEN_H
#define QUEEN_H

#include "Bishop.h"

// Queen class inherits from Bishop
class Queen : public Bishop {
    public:
        Queen(bool isWhite, int x, int y); // Constructor
        void draw(sf::RenderWindow &window); // Draw the Queen
        virtual std::vector<Move> getPossibleMoves(Board& board); // Get possible moves
        bool isSwappable(bool isWhite); // Check if swappable
};

#endif
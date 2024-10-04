#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop: public Piece {
    public:
        Bishop(bool isWhile, int x, int y);
        void draw(sf::RenderWindow &window);
        virtual std::vector<Move> getPossibleMoves(Board& board);
        bool isSwappable(bool isWhite);
};
#endif
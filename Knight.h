#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece {
    public:
        Knight(bool isWhile, int x, int y);
        void draw(sf::RenderWindow &window);
        virtual std::vector<Move> getPossibleMoves(Board& board);
        bool isKnight();
        bool isSwappable(bool isWhite);
};


#endif
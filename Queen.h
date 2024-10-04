#ifndef QUEEN_H
#define QUEEN_H

#include "Bishop.h"

class Piece;
class Queen : public Bishop {
    public:
        Queen(bool isWhile, int x, int y);
        void draw(sf::RenderWindow &window);
        virtual std::vector<Move> getPossibleMoves(Board& board);
        bool isQueen();
        bool isSwappable(bool isWhite);

};
#endif
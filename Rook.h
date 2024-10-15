#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook: public Piece {
    private: 
        bool firstMove;
        bool castle;
    public:
        Rook(bool isWhile, int x, int y);
        void draw(sf::RenderWindow &window);
        virtual std::vector<Move> getPossibleMoves(Board& board);
        bool isSwappable(bool isWhite);
        bool getFirstMove();
        void doFirstMove();
};
#endif
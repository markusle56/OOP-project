#ifndef BROOK_H
#define BROOK_H

#include "Piece.h"

class Brook: public Piece {
    private: 
        bool firstMove;
        bool castle;
    public:
        Brook(bool isWhile, int x, int y);
        void draw(sf::RenderWindow &window);
        virtual std::vector<Move> getPossibleMoves(Board& board);
        bool isBrook();
        bool isSwappable(bool isWhite);
};
#endif
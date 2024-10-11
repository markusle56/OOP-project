#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"


class Pawn : public Piece {
    private: 
        bool firstMove; 
    public:
        Pawn(bool isWhite, int x, int y);
        virtual std::vector<Move> getPossibleMoves(Board& board);
        void draw(sf::RenderWindow& window);
        bool isSwappable(bool isWhite);
        void doFirstMove();

};
#endif
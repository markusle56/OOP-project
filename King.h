#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {
    private: 
        bool firstMove;
        bool castle;
    public:
        King(bool isWhite, int x, int y);
        std::vector<Move> getPossibleMoves(Board& board);
        void draw(sf::RenderWindow& window);
        bool isSwappable(bool isWhite);
};

#endif
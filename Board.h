#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include "Piece.h"

class Board {
    private:
        Piece * board[8][8];
    public:
        Board();
        ~Borad();
        void setupBoard();
        void draw(sf::RenderWindow& window);
        bool isMoveLegal(const Move& move);
        bool isCheck(bool isWhite);
        Piece* getPieceAt(int x, int y);
        void movePiece(const Move& move);
        // Additional functions as needed
};
#endif
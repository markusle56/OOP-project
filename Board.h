#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include "Piece.h"
#include "Pawn.h"
#include <vector>

class Board {
    private:
        Piece * board[8][8];
        sf::Texture texture;
        sf::Sprite sprite;
        std::string textureFilePath;
        std::vector<Move> move_history;
    public:
        Board();
        ~Board();
        void setupBoard();
        void draw(sf::RenderWindow& window);
        // bool isMoveLegal(const Move& move);
        // bool isCheck(bool isWhite);
        Piece* getPieceAt(int x, int y);
        void movePiece(const Move& move);

};
#endif
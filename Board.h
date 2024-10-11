#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include "Move.h"
#include "Piece.h"
#include "Pawn.h"
#include "King.h"
#include "Bishop.h"
#include "Brook.h"
#include "Queen.h"
#include "Knight.h"
#include <vector>
#include <cstdlib> 
#include <ctime>   
#include <string>

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
        void drawBoard(sf::RenderWindow& window);
        sf::Vector2i isCheck(bool isWhite);
        Piece* getPieceAt(int x, int y);
        void movePiece(const Move& move);
        void swap(Piece * piece);
        void drawPieces(sf::RenderWindow &window);
        Piece * canPromote();
        bool promote(Piece * piece, std::string intoPiece);
};
#endif
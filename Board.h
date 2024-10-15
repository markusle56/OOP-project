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

// The Board class manages the chessboard, pieces, and game logic.
class Board {
    private:
        Piece* board[8][8];              // 2D array representing the chessboard with pieces
        sf::Texture texture;             // Texture for the board
        sf::Sprite sprite;               // Sprite to display the board
        std::string textureFilePath;     // File path for the texture
        std::vector<Move> move_history;  // History of all moves made in the game
    public:
        Board();                         // Constructor
        ~Board();                        // Destructor
        void setupBoard();               // Set up initial chessboard with pieces
        void drawBoard(sf::RenderWindow& window); // Draw the chessboard
        sf::Vector2i isCheck(bool isWhite); // Check if a player is in check
        Piece* getPieceAt(int x, int y);  // Get the piece at a specific position
        void movePiece(const Move& move); // Move a piece based on the given move
        void swap(Piece* piece);          // Swap a piece's position if needed
        void drawPieces(sf::RenderWindow& window); // Draw all the pieces on the board
        Piece* canPromote();              // Check if a pawn can be promoted
        bool promote(Piece* piece, std::string intoPiece); // Promote a pawn to a new piece
};

#endif

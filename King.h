#ifndef KING_H
#define KING_H

#include "Piece.h"
#include "Rook.h"

// King class inherits from Piece
class King : public Piece {
    private: 
        bool firstMove; // Tracks if King has moved
    public:
        King(bool isWhite, int x, int y); // Constructor
        std::vector<Move> getPossibleMoves(Board& board); // Get possible moves
        void draw(sf::RenderWindow& window); // Draw the King
        bool isSwappable(bool isWhite); // Check if swappable
        bool canCastle(Board& board); // Check if castling is possible
        bool castleKingSide(Board& board); // Perform kingside castling
        bool castleQueenSide(Board& board); // Perform queenside castling
        void doFirstMove(); // Mark that the first move has been made
};

#endif
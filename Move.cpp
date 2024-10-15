#include "Move.h"
#include "Board.h"
#include "Piece.h"

// Constructor to initialize the move and set the captured piece (if any)
Move::Move(int startX, int startY, int endX, int endY, Piece* captured) : startX(startX), startY(startY), endX(endX), endY(endY), captured_piece(captured) {}

void Move::execute(Board& board) {
    // Retrieve the piece from the starting position
    Piece* movingPiece = board.getPieceAt(startX, startY);
    if (movingPiece) {
        // Move the piece on the board
        board.movePiece(*this);
        // If there is a captured piece, delete it
        if (captured_piece) {
            delete captured_piece;
        }
    }
    return;
}

// Check if the move targets the specified piece
bool Move::isTargeted(Piece *piece) {
    if (endX == piece->getX() && endY == piece->getY()) {
        return true;
    }
    return false;
}

// Draw the move as a highlighted circle on the board
void Move::draw(sf::RenderWindow& window) {
    sf::CircleShape highlightedCircle(15);
    // Set the position of the highlighted circle
    highlightedCircle.setPosition(endX * 100 + 35, endY * 100 + 35);
    // Set the color based on whether a piece was captured or not
    if (captured_piece == nullptr) {
        highlightedCircle.setFillColor(sf::Color(80, 80, 80, 200)); // Grey color
    } else {
        highlightedCircle.setFillColor(sf::Color(194, 24, 7, 130)); // Red color for capture
    }
    // Draw the highlighted circle
    window.draw(highlightedCircle); 
}

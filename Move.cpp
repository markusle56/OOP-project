#include "Move.h"
#include "Board.h"
#include "Piece.h"

Move::Move(int startX, int startY, int endX, int endY, Piece* captured): startX(startX), startY(startY), endX(endX), endY(endY), captured_piece(captured) {}

bool Move::isValid() const {
    return true;
}
void Move::execute(Board& board) {
    Piece* movingPiece = board.getPieceAt(startX, startY);
    if(movingPiece)
    {
        board.movePiece(*this);
        if(captured_piece)
        {
            delete captured_piece;
        }
    }
    return;
}

bool Move::isTargeted(Piece *piece) {
    if (endX == piece->getX() && endY == piece->getY())
    {
        return true;
    }
    return false;
}

void Move::draw(sf::RenderWindow& window) {
    sf::RectangleShape highlightedSquare(sf::Vector2f(100, 100));
    highlightedSquare.setPosition(endX * 100, endY * 100);
    if (captured_piece == nullptr) {
        highlightedSquare.setFillColor(sf::Color(255,255,51 , 100));
    } else {
        highlightedSquare.setFillColor(sf::Color(194,24,7 , 100));
    }

    window.draw(highlightedSquare); 
}
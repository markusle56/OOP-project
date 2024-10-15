#include "Move.h"
#include "Board.h"
#include "Piece.h"

Move::Move(int startX, int startY, int endX, int endY, Piece* captured): startX(startX), startY(startY), endX(endX), endY(endY), captured_piece(captured) {}

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
    sf::CircleShape highlightedCircle(15);
    highlightedCircle.setPosition(endX * 100+35, endY * 100 + 35 );
    if (captured_piece == nullptr) {
        highlightedCircle.setFillColor(sf::Color(80,80,80 , 200));
    } else {
        highlightedCircle.setFillColor(sf::Color(194,24,7 , 130));
    }

    window.draw(highlightedCircle); 
}
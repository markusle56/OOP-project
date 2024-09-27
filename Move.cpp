#include "Move.h"
#include "Board.h"

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
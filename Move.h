#ifndef MOVE_H
#define MOVE_H

#include "Piece.h"

class Move
{
public:
    Move(int startX, int startY, int endX, int endY, Piece* captured);
    bool isValid() const;
    void execute(Board& board);
    // Additional functions as needed

    int startX, startY;
    int endX, endY;
    Piece* captured_piece;
};

#endif

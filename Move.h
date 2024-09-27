#ifndef MOVE_H
#define MOVE_H

class Piece;
class Board;

class Move
{
public:
    Move(int startX, int startY, int endX, int endY, Piece* captured);
    bool isValid() const;
    void execute(Board& board);

    int startX, startY;
    int endX, endY;
    Piece* captured_piece;
};

#endif

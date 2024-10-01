#ifndef MOVE_H
#define MOVE_H

#include "Piece.h"

class Piece;
class Board;

class Move
{

public:
    int startX, startY;
    int endX, endY;
    Piece* captured_piece;

    Move(int startX, int startY, int endX, int endY, Piece* captured);
    bool isValid() const;
    void execute(Board& board);
    bool isTargeted(Piece * piece);
    void draw(sf::RenderWindow &window);

   
};

#endif

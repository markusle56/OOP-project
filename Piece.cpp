#include "Piece.h"
#include "Move.h" // Include when needed
#include "Board.h" // Include when needed

Piece::Piece(bool isWhite, int x, int y): isWhite(isWhite), x(x), y(y) {}

Piece::~Piece() {}

void Piece::draw(sf::RenderWindow& window) {}

void Piece::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
    float posX = 100*x + 10;
    float posY = 100*y + 10;
    sf::Vector2f Pos(posX,posY);
    sprite.setPosition(Pos);
    return;
}


int Piece::getX() {return x;}
int Piece::getY() {return y;}

bool Piece::getIsWhite() { return isWhite;}


std::vector<Move> Piece::getPossibleMoves(Board& board) { 
    std::vector<Move> pieces;
    return pieces;}

bool Piece::isKing(bool isWhite) {return false;}

bool Piece::isQueen(bool isWhite) {return false;}

bool Piece::isSwappable(bool isWhite) {
    return false;
}

sf::Vector2i Piece::getPosition() {return sf::Vector2i(x,y);}


bool Piece::isPawn() {return false;}

void Piece::doFirstMove() {return;}
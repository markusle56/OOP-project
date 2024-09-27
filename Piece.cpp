#include "Piece.h"

Piece::Piece(bool isWhite, int x, int y): isWhite(isWhite), x(x), y(y) {}

Piece::~Piece() {}

void Piece::draw(sf::RenderWindow& window) {}

void Piece::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
    sprite.setPosition(calculatePosition());
    return;
}

sf::Vector2f Piece::calculatePosition() {
    float posX = 125*x + 7 ;
    float posY = 125*y + 10;
    sf::Vector2f Pos(posX,posY);
    return Pos;
}

int Piece::getX() {return x;}
int Piece::getY() {return y;}
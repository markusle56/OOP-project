#include "Piece.h"

Piece::Piece(bool isWhite, int x, int y): isWhite(isWhite), x(x), y(y) {}

Piece::~Piece() {}

void Piece::draw(sf::RenderWindow& window) {}

void Piece::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
    float posX = 100*x;
    float posY = 100*y;
    sf::Vector2f Pos(posX,posY);
    sprite.setPosition(Pos);
    return;
}


int Piece::getX() {return x;}
int Piece::getY() {return y;}

bool Piece::getIsWhite() { return isWhite;}


std::vector<Move> Piece::getPossibleMoves(Board& board) {}

bool Piece::isKing(bool isWhite) {return false;}

bool Piece::isSwappable(bool isWhite) {
    return false;
}

sf::Vector2i Piece::getPosition() {return sf::Vector2i(x,y);}
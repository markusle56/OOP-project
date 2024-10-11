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


bool Piece::isSwappable(bool isWhite) {
    return false;
}

sf::Vector2i Piece::getPosition() {return sf::Vector2i(x,y);}


bool Piece::isPawn() {return false;}

void Piece::doFirstMove() {return;}

std::string Piece::getName() {return name;}

void Piece::draw_background(sf::RenderWindow& window, std::string color) {
    sf::RectangleShape highlightedSquare(sf::Vector2f(100, 100));
    highlightedSquare.setPosition(x * 100, y * 100);
    if (color == "yellow") {
        highlightedSquare.setFillColor(sf::Color(255,255,51 , 100));
    } else if (color == "red") {
        highlightedSquare.setFillColor(sf::Color(194,24,7 , 255));
    }
    window.draw(highlightedSquare); 
}
#include "Piece.h"
#include "Move.h" // Include when needed
#include "Board.h" // Include when needed

// Constructor initializes piece's color and position
Piece::Piece(bool isWhite, int x, int y): isWhite(isWhite), x(x), y(y) {}

// Destructor
Piece::~Piece() {}

// Empty draw function (to be overridden by derived classes)
void Piece::draw(sf::RenderWindow& window) {}

// Set the position of the piece on the board
void Piece::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
    float posX = 100 * x + 10;
    float posY = 100 * y + 10;
    sf::Vector2f Pos(posX,posY);
    sprite.setPosition(Pos);
    return;
}

// Return the X position of the piece
int Piece::getX() { return x; }

// Return the Y position of the piece
int Piece::getY() { return y; }

// Return true if the piece is white
bool Piece::getIsWhite() { return isWhite; }

// Return an empty list of moves (to be overridden by derived classes)
std::vector<Move> Piece::getPossibleMoves(Board& board) { 
    std::vector<Move> pieces;
    return pieces;
}

// Default: piece is not swappable
bool Piece::isSwappable(bool isWhite) { return false; }

// Return the position of the piece as a Vector2i
sf::Vector2i Piece::getPosition() { return sf::Vector2i(x, y); }

// Default: piece is not a pawn
bool Piece::isPawn() { return false; }

// Default function for first move (to be overridden by derived classes)
void Piece::doFirstMove() { return; }

// Return the name of the piece
std::string Piece::getName() { return name; }

// Draw a background highlight around the piece
void Piece::draw_background(sf::RenderWindow& window, std::string color) {
    sf::RectangleShape highlightedSquare(sf::Vector2f(100, 100));
    highlightedSquare.setPosition(x * 100, y * 100); 
    if (color == "yellow") {
        highlightedSquare.setFillColor(sf::Color(255, 255, 51, 100)); // Yellow highlight
    } else if (color == "red") {
        highlightedSquare.setFillColor(sf::Color(194, 24, 7, 255)); // Red highlight
    }
    window.draw(highlightedSquare); 
}
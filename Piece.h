#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Move; // Forward declaration of Move
class Board; // Forward declaration of Board

// Base class for all chess pieces
class Piece {
    protected:
        int x, y; // Piece's position on the board
        std::string name; // Name of the piece
        bool isWhite; // Indicates if the piece is white
        sf::Texture texture; // Texture for the piece
        sf::Sprite sprite; // Sprite for rendering the piece
        std::string textureFilePath; // File path for the texture
        bool isClicked; // Tracks if the piece is clicked
    public:
        virtual void draw(sf::RenderWindow& window); // Draw the piece
        Piece(bool isWhite, int x, int y); // Constructor
        void setPosition(int x, int y); // Set piece position
        ~Piece(); // Destructor
        virtual std::vector<Move> getPossibleMoves(Board& board); // Get valid moves
        int getX(); // Get x position
        int getY(); // Get y position
        virtual std::string getName(); // Get the piece name
        bool getIsWhite(); // Check if piece is white
        virtual bool isSwappable(bool isWhite); // Check if piece is swappable
        sf::Vector2i getPosition(); // Get piece position
        virtual bool isPawn(); // Check if piece is a pawn
        virtual void doFirstMove(); // Mark first move
        void draw_background(sf::RenderWindow& window, std::string color); // Draw background
};

#endif
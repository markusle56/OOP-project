#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Move;  // Forward declaration of Move
class Board; // Forward declaration of Board

class Piece {
    protected:
        int x; 
        int y;
        std::string name;
        bool isWhite;
        sf::Texture texture;
        sf::Sprite sprite;
        std::string textureFilePath;
    public: 
        virtual void draw(sf::RenderWindow& window);
        Piece(bool isWhite,int x, int y);
        void setPosition(int x, int y);
        ~Piece();
        virtual std::vector<Move> getPossibleMoves(Board& board);
        int getX();
        int getY();
        virtual std::string getName();
        bool getIsWhite();
        virtual bool isSwappable(bool isWhite);
        sf::Vector2i getPosition();
        virtual bool isPawn();
        virtual void doFirstMove();
};
#endif
#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Move.h"
#include "Board.h"

class Piece{
    protected:
        int x; 
        int y;
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
        bool isW();
        
};
#endif
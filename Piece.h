#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>
#include <vector>

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
        ~Piece();
        
};
#endif
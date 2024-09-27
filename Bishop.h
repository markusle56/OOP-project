#ifndef BISHOP_H
#define BISHOP_H
#include <SFML/Graphics.hpp>
#include <Piece.h>

class Bishop: public Piece {
    public:
        Bishop();
        ~Bishop();
        void draw(sf::RenderWindow &window );
};
#endif
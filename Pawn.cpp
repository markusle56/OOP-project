#include "Pawn.h"


Pawn::Pawn(bool isWhite, int x, int y): Piece(isWhite, x,y) {
    if(isWhite) {
        textureFilePath = "IMG/Pawn_B.png";
    } else {
        textureFilePath = "IMG/Pawn_W.png";
    }
    if (!texture.loadFromFile(textureFilePath))
    {
        
    }
    sprite.setTexture(texture);
}

void Pawn::draw(sf::RenderWindow& window) {
    sprite.setScale(0.2,0.2);
    sprite.setPosition(x*125 + 7,y*125 + 10);
    window.draw(sprite);
}

bool Pawn::canPromote() {
    if (isWhite) {
        if (y == 7) {
            return true;
        } else {
            return false;
        }
    } else {
        if (y == 0) {
            return true;
        } else {
            return false;
        }
    }
}
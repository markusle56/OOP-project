#include "King.h"
#include "Board.h"
#include "iostream"

King::King(bool isWhite, int x, int y): Piece(isWhite, x, y), castle(false) {
    if(isWhite) {
        textureFilePath = "IMG/King_W.png";
    } else {
        textureFilePath = "IMG/King_B.png";
    }
    if (!texture.loadFromFile(textureFilePath))
    {
        std::cout<<"ERROR.....Could not load the King image"<<std::endl;
    }
    sprite.setTexture(texture);
}

void King::draw(sf::RenderWindow& window) {
    sprite.setScale(0.15,0.15);
    this->setPosition(x,y);
    window.draw(sprite);
}

std::vector<Move> King::getPossibleMoves(Board& board) {
    std::vector<Move> moves;
    for (int x1 = -1; x1 <= 1; x1++) {
        for (int y1 = -1; y1 <= 1; y1++) {
            
            int newX = x + x1;
            int newY = y + y1;

            if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
                Piece* targetedPiece = board.getPieceAt(newX, newY);
                if (targetedPiece == nullptr) {
                    moves.emplace_back(x, y, newX, newY, nullptr);
                } else if (targetedPiece->getIsWhite() != isWhite) {
                    moves.emplace_back(x, y, newX, newY, targetedPiece);
                }
            }
        }
    }
    return moves;    
}

bool King::isKing() {return true;}

bool King::isSwappable(bool isWhite) {return false;}
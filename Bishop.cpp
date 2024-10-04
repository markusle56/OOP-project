#include "Bishop.h"
#include "Board.h"
#include "iostream"

Bishop::Bishop(bool isWhite, int x, int y) : Piece(isWhite, x, y) {
    if(isWhite) {
        textureFilePath = "IMG/Bishop_W.png";
    } else {
        textureFilePath = "IMG/Bishop_B.png";
    }
    if (!texture.loadFromFile(textureFilePath))
    {
        
    }
    sprite.setTexture(texture);
}

void Bishop::draw(sf::RenderWindow &window ) {
    sprite.setScale(0.15,0.15);
    this->setPosition(x,y);
    window.draw(sprite);
}

std::vector<Move> Bishop::getPossibleMoves(Board& board) {
    std::vector<Move> moves;
    //(+x, +y)
    for (int i = 1; i < 8; i++) {
        
        int newX = x + i;
        int newY = y + i;

        if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
            Piece* targetedPiece = board.getPieceAt(newX, newY);
            if (targetedPiece == nullptr) {
                moves.emplace_back(x, y, newX, newY, nullptr);
            } else if (targetedPiece->getIsWhite() != isWhite) {
                moves.emplace_back(x, y, newX, newY, targetedPiece);
                break;
            } else {
                break;
            }
        }
    }
    //(-x, +y)
    for (int i = 1; i < 8; i++) {
        
        int newX = x - i;
        int newY = y + i;

        if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
            Piece* targetedPiece = board.getPieceAt(newX, newY);
            if (targetedPiece == nullptr) {
                moves.emplace_back(x, y, newX, newY, nullptr);
            } else if (targetedPiece->getIsWhite() != isWhite) {
                moves.emplace_back(x, y, newX, newY, targetedPiece);
                break;
            } else {
                break;
            }
        }
    }
    //(+x, -y)
    for (int i = 1; i < 8; i++) {
        
        int newX = x + i;
        int newY = y - i;

        if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
            Piece* targetedPiece = board.getPieceAt(newX, newY);
            if (targetedPiece == nullptr) {
                moves.emplace_back(x, y, newX, newY, nullptr);
            } else if (targetedPiece->getIsWhite() != isWhite) {
                moves.emplace_back(x, y, newX, newY, targetedPiece);
                break;
            } else {
                break;
            }
        }
    }
    //(-x,-y)
    for (int i = 1; i < 8; i++) {
        
        int newX = x - i;
        int newY = y - i;

        if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
            Piece* targetedPiece = board.getPieceAt(newX, newY);
            if (targetedPiece == nullptr) {
                moves.emplace_back(x, y, newX, newY, nullptr);
            } else if (targetedPiece->getIsWhite() != isWhite) {
                moves.emplace_back(x, y, newX, newY, targetedPiece);
                break;
            } else {
                break;
            }
        }
    }

    return moves;
}

bool Bishop::isBishop() {return true;}

bool Bishop::isSwappable(bool isWhite) {
    if (this->isWhite == isWhite) {
        return true;
    }
    return false;
}
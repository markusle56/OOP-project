#include "Pawn.h"
#include "Board.h"
#include "iostream"


Pawn::Pawn(bool isWhite, int x, int y): Piece(isWhite, x,y), firstMove(true){
    name = "Pawn";
    if(isWhite) {
        textureFilePath = "IMG/Pawn_W.png";
    } else {
        textureFilePath = "IMG/Pawn_B.png";
    }
    if (!texture.loadFromFile(textureFilePath))
    {
        std::cout<<"ERROR.....Could not load the Pawn image"<<std::endl;
    }
    sprite.setTexture(texture);
}

void Pawn::draw(sf::RenderWindow& window) {
    sprite.setScale(0.15,0.15);
    this->setPosition(x,y);
    window.draw(sprite);
}

bool Pawn::canPromote() {
    if (isWhite) {
        if (x == 0) {
            return true;
        } else {
            return false;
        }
    } else {
        if (x == 7) {
            return true;
        } else {
            return false;
        }
    }
}


std::vector<Move> Pawn::getPossibleMoves(Board& board) {
    std::vector<Move> moves;

    int direction; 
    if (isWhite) {
        direction = -1;
    } else {
        direction = 1; 
    }
    int newY = y + direction;
    if (board.getPieceAt(x, newY) == nullptr) {
        moves.emplace_back(x,y,x,newY,nullptr);
        if (firstMove == true && board.getPieceAt(x, newY + direction) == nullptr) {
            std::cout<<"run first move"<<std::endl;
            moves.emplace_back(x,y,x,newY + direction,nullptr);
        }
    }

    if (x+1 <= 7 && board.getPieceAt(x+1,newY) && board.getPieceAt(x+1, newY)->getIsWhite() != isWhite) {
        moves.emplace_back(x,y,x+1,newY,board.getPieceAt(x+1, newY));
    } 
    if (x-1 >= 0 && board.getPieceAt(x-1,newY) && board.getPieceAt(x-1, newY)->getIsWhite() != isWhite) {
        moves.emplace_back(x,y,x-1,newY,board.getPieceAt(x-1, newY));
    }

    return moves;
}

bool Pawn::isSwappable(bool isWhite) { 
    if (this->isWhite == isWhite) {
        return true;
    }
    return false;
}


void Pawn::doFirstMove() {
    firstMove = false;
    if (!firstMove) {}
    return;
}
#include "Knight.h"
#include "Board.h"
#include "iostream"

Knight::Knight(bool isWhite, int x, int y) : Piece(isWhite, x, y) {
    name = "Knight";
    if(isWhite) {
        textureFilePath = "IMG/Knight_W.png";
    } else {
        textureFilePath = "IMG/Knight_B.png";
    }
    if (!texture.loadFromFile(textureFilePath))
    {
        std::cout<<"ERROR.....Could not load the Knight image"<<std::endl;
    }
    sprite.setTexture(texture);
}

void Knight::draw(sf::RenderWindow &window ) {
    sprite.setScale(0.15,0.15);
    this->setPosition(x,y);
    window.draw(sprite);
}

std::vector<Move> Knight::getPossibleMoves(Board& board) {
    std::vector<Move> moves;
    int moveSet[8][2] = {{2,1}, {2,-1}, {-2,-1}, {-2,1}, {1,2}, {1,-2}, {-1,2}, {-1,-2}};
    for (int i = 0; i < 8; i++) {

        int newX = x + moveSet[i][0];
        int newY = y + moveSet[i][1];

        if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
            Piece* targetedPiece = board.getPieceAt(newX, newY);
            if (targetedPiece == nullptr) {
                moves.emplace_back(x, y, newX, newY, nullptr);
            } else if (targetedPiece->getIsWhite() != isWhite) {
                moves.emplace_back(x, y, newX, newY, targetedPiece);
            }
        }
    }
    return moves;
}

bool Knight::isSwappable(bool isWhite) {
    if (this->isWhite == isWhite) {
        return true;
    }
    return false;
}
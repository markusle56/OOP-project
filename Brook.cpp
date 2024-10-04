#include "Brook.h"
#include "Board.h"
#include "iostream"

Brook::Brook(bool isWhite, int x, int y): Piece(isWhite, x,y), firstMove(true) {
    if(isWhite) {
        textureFilePath = "IMG/Brook_W.png";
    } else {
        textureFilePath = "IMG/Brook_B.png";
    }
    if (!texture.loadFromFile(textureFilePath))
    {
        std::cout<<"ERROR.....Could not load the brook image"<<std::endl;
    }
    sprite.setTexture(texture);
}

void Brook::draw(sf::RenderWindow &window) {
    sprite.setScale(0.15,0.15);
    this->setPosition(x,y);
    window.draw(sprite);
}

std::vector<Move> Brook::getPossibleMoves(Board& board) {
    std::vector<Move> moves;

    for (int x1 = 1; x1 < 8; x1++) {
        int newX = x + x1;

        if (newX >= 0 && newX < 8) {
            Piece* targetedPiece = board.getPieceAt(newX, y);
            if (targetedPiece == nullptr) {
                moves.emplace_back(x, y, newX, y, nullptr);
            } else if (targetedPiece->getIsWhite() != isWhite) {
                moves.emplace_back(x, y, newX, y, targetedPiece);
                break;
            } else {
                break;
            }
        }
    }

    for (int x1 = 1; x1 < 8; x1++) {
        int newX = x - x1;

        if (newX >= 0 && newX < 8) {
            Piece* targetedPiece = board.getPieceAt(newX, y);
            if (targetedPiece == nullptr) {
                moves.emplace_back(x, y, newX, y, nullptr);
            } else if (targetedPiece->getIsWhite() != isWhite) {
                moves.emplace_back(x, y, newX, y, targetedPiece);
                break;
            } else {
                break;
            }
        }
    }

    for (int y1 = 1; y1 < 8; y1++) {
        int newY = y + y1;

        if (newY >= 0 && newY < 8) {
            Piece* targetedPiece = board.getPieceAt(x, newY);
            if (targetedPiece == nullptr) {
                moves.emplace_back(x, y, x, newY, nullptr);
            } else if (targetedPiece->getIsWhite() != isWhite) {
                moves.emplace_back(x, y, x, newY, targetedPiece);
                break;
            } else {
                break;
            }
        }
    }

    for (int y1 = 1; y1 < 8; y1++) {
        int newY = y - y1;

        if (newY >= 0 && newY < 8) {
            Piece* targetedPiece = board.getPieceAt(x, newY);
            if (targetedPiece == nullptr) {
                moves.emplace_back(x, y, x, newY, nullptr);
            } else if (targetedPiece->getIsWhite() != isWhite) {
                moves.emplace_back(x, y, x, newY, targetedPiece);
                break;
            } else {
                break;
            }
        }
    }

    return moves;
}


bool Brook::isSwappable(bool isWhite) {
    if (this->isWhite == isWhite) {
        return true;
    }
    return false;
}

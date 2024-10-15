#include "King.h"
#include "Board.h"
#include "iostream"

King::King(bool isWhite, int x, int y): Piece(isWhite, x, y), castle(true), firstMove(true) {
    name = "King";
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

    if (canCastle(board)) {
        if (castleKingSide(board)) {
            moves.emplace_back(x, y, x+2, y, nullptr);
        }
        if (castleQueenSide(board)) {
            moves.emplace_back(x, y, x-2, y, nullptr);
        }
    }
    return moves;
}


bool King::isSwappable(bool isWhite) {return false;}

void King::doFirstMove() {
    firstMove = false;
    if (!firstMove) {}
    return;
}

bool King::canCastle(Board& board) {
    if (!firstMove) {
        return false;
    }
    return true;
}

bool King::castleKingSide(Board& board) {
    if (!canCastle(board)) {
        return false;
    }

    if (board.getPieceAt(x + 1, y) != nullptr || board.getPieceAt(x + 2, y) != nullptr) {
        return false;
    }

    Piece* piece = board.getPieceAt(x + 3, y); 
    Rook* rook = dynamic_cast<Rook*>(piece);
    if (rook == nullptr || !rook->getFirstMove() || rook->getName() != "Rook") {
        return false;
    }
    return true;
}

bool King::castleQueenSide(Board& board) {
    if (!canCastle(board)) {
        return false;
    }

    if (board.getPieceAt(x - 1, y) != nullptr || board.getPieceAt(x - 2, y) != nullptr || board.getPieceAt(x - 3, y) != nullptr) {
        return false;
    }

    Piece* piece = board.getPieceAt(x - 4, y); 
    Rook* rook = dynamic_cast<Rook*>(piece);
    if (rook == nullptr || !rook->getFirstMove() || rook->getName() != "Rook") {
        return false;
    }
    return true;
}
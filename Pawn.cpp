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

std::vector<Move> Pawn::getPossibleMoves(Board& board) {
    std::vector<Move> moves;
    
    int direction = isWhite ? -1 : 1; // Determine direction based on color
    int newY = y + direction;

    // Ensure newY is within bounds before accessing the board
    if (newY >= 0 && newY <= 7) {
        // Move forward by 1 square
        if (board.getPieceAt(x, newY) == nullptr) {
            moves.emplace_back(x, y, x, newY, nullptr);

            // Move forward by 2 squares if it's the first move
            if (firstMove == true && newY + direction >= 0 && newY + direction <= 7 
                && board.getPieceAt(x, newY + direction) == nullptr) {
                moves.emplace_back(x, y, x, newY + direction, nullptr);
            }
        }

        // Diagonal capture to the right
        if (x + 1 <= 7 && board.getPieceAt(x + 1, newY) && 
            board.getPieceAt(x + 1, newY)->getIsWhite() != isWhite) {
            moves.emplace_back(x, y, x + 1, newY, board.getPieceAt(x + 1, newY));
        }

        // Diagonal capture to the left
        if (x - 1 >= 0 && board.getPieceAt(x - 1, newY) && 
            board.getPieceAt(x - 1, newY)->getIsWhite() != isWhite) {
            moves.emplace_back(x, y, x - 1, newY, board.getPieceAt(x - 1, newY));
        }
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
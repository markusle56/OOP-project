#include "Rook.h"
#include "Board.h"
#include "iostream"

// Rook constructor, initializes Rook with texture based on color
Rook::Rook(bool isWhite, int x, int y): Piece(isWhite, x,y), firstMove(true) {
    name = "Rook";
    if(isWhite) {
        textureFilePath = "IMG/Rook_W.png";
    } else {
        textureFilePath = "IMG/Rook_B.png";
    }
    if (!texture.loadFromFile(textureFilePath)) {
        std::cout << "ERROR.....Could not load the Rook image" << std::endl;
    }
    sprite.setTexture(texture);
}

// Draw the Rook on the board
void Rook::draw(sf::RenderWindow &window) {
    sprite.setScale(0.15,0.15); // Scale image
    this->setPosition(x,y); // Position the Rook
    window.draw(sprite); // Render it
}

// Get possible moves for the Rook
std::vector<Move> Rook::getPossibleMoves(Board& board) {
    std::vector<Move> moves;

    // Horizontal movement to the right
    for (int x1 = 1; x1 < 8; x1++) {
        int newX = x + x1;
        if (newX >= 0 && newX < 8) {
            Piece* targetedPiece = board.getPieceAt(newX, y);
            // Empty space, add move
            if (targetedPiece == nullptr) {
                moves.emplace_back(x, y, newX, y, nullptr);
            // Opponent's piece, add capture and stop
            } else if (targetedPiece->getIsWhite() != isWhite) {
                moves.emplace_back(x, y, newX, y, targetedPiece);
                break;
            } else {
                // Friendly piece, stop
                break;
            }
        }
    }
    // Horizontal movement to the left
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
    // Vertical movement upwards
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
    // Vertical movement downwards
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

    // Return possible moves
    return moves;
}

// Check if Rook can be swapped based on color
bool Rook::isSwappable(bool isWhite) {
    if (this->isWhite == isWhite) {
        return true;
    }
    return false;
}

// Return whether the Rook has moved
bool Rook::getFirstMove() { return firstMove; }

// Mark that the Rook has made its first move
void Rook::doFirstMove() {
    firstMove = false;
    if (!firstMove) {}
    return;
}
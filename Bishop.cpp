#include "Bishop.h"
#include "Board.h"
#include "iostream"

// Bishop constructor, initializes Bishop with texture based on color
Bishop::Bishop(bool isWhite, int x, int y) : Piece(isWhite, x, y) {
    name = "Bishop";
    if(isWhite) {
        textureFilePath = "IMG/Bishop_W.png";
    } else {
        textureFilePath = "IMG/Bishop_B.png";
    }
    if (!texture.loadFromFile(textureFilePath))
    {
        std::cout << "ERROR.....Could not load the Bishop image" << std::endl;
    }
    sprite.setTexture(texture);
}

// Draw the Bishop on the board
void Bishop::draw(sf::RenderWindow &window) {
    sprite.setScale(0.15, 0.15); // Scale the image
    this->setPosition(x, y); // Position the Bishop
    window.draw(sprite); // Render it
}

// Get possible moves for Bishop
std::vector<Move> Bishop::getPossibleMoves(Board& board) {
    std::vector<Move> moves;

    // Move diagonally (+x, +y) 
    for (int i = 1; i < 8; i++) {
        int newX = x + i, newY = y + i;
        // Check if within board boundaries
        if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
            Piece* targetedPiece = board.getPieceAt(newX, newY);
            // Empty space, add move
            if (targetedPiece == nullptr) {
                moves.emplace_back(x, y, newX, newY, nullptr);
            // Opponent's piece, add capture and stop
            } else if (targetedPiece->getIsWhite() != isWhite) {
                moves.emplace_back(x, y, newX, newY, targetedPiece);
                break;
            } else {
                // Friendly piece, stop
                break;
            }
        }
    }

    // Move diagonally (-x, +y) 
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
    // Move diagonally (+x, -y)
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
    // Move diagonally (-x,-y)
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

    // Return list of valid moves
    return moves;
}

// Check if the Bishop can swap based on color
bool Bishop::isSwappable(bool isWhite) {
    if (this->isWhite == isWhite) {
        return true;
    }
    return false;
}
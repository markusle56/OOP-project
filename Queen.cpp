#include "Queen.h"
#include "Board.h"
#include "iostream"

// Queen constructor, initializes Queen with texture based on color
Queen::Queen(bool isWhite, int x, int y) : Bishop(isWhite, x, y) {
    name = "Queen";
    if(isWhite) {
        textureFilePath = "IMG/Queen_W.png";
    } else {
        textureFilePath = "IMG/Queen_B.png";
    }
    if (!texture.loadFromFile(textureFilePath))
    {
        std::cout << "ERROR.....Could not load the Queen image" << std::endl;
    }
    sprite.setTexture(texture);
}

// Draw the Queen on the board
void Queen::draw(sf::RenderWindow &window ) {
    sprite.setScale(0.15, 0.15); // Scale image
    this->setPosition(x, y); // Position the Queen
    window.draw(sprite); // Render it
}

// Get possible moves for the Queen
std::vector<Move> Queen::getPossibleMoves(Board& board) {
    // Use Bishop's diagonal moves
    std::vector<Move> moves = Bishop::getPossibleMoves(board);

    // Horizontal movement to the right
    for (int x1 = 1; x1 < 8; x1++) {
        int newX = x + x1;
        // Ensure the move is within board boundaries
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

// Queen is not swappable
bool Queen::isSwappable(bool isWhite) { return false; }
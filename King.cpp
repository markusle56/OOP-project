#include "King.h"
#include "Board.h"
#include "iostream"

// King constructor, initializes King with texture based on color
King::King(bool isWhite, int x, int y): Piece(isWhite, x, y), firstMove(true) {
    name = "King";
    if(isWhite) {
        textureFilePath = "IMG/King_W.png";
    } else {
        textureFilePath = "IMG/King_B.png";
    }
    if (!texture.loadFromFile(textureFilePath))
    {
        std::cout << "ERROR.....Could not load the King image" << std::endl;
    }
    sprite.setTexture(texture);
}

// Draw the King on the board
void King::draw(sf::RenderWindow& window) {
    sprite.setScale(0.15, 0.15); // Scale image
    this->setPosition(x, y); // Position the King
    window.draw(sprite); // Render it
}

// Get possible moves for the King
std::vector<Move> King::getPossibleMoves(Board& board) {
    std::vector<Move> moves;

    // Check all adjacent squares (-1, 0, +1 in both x and y)
    for (int x1 = -1; x1 <= 1; x1++) {
        for (int y1 = -1; y1 <= 1; y1++) {
            int newX = x + x1;
            int newY = y + y1;
            // Ensure new position is within the board
            if (newX != x || newY != y) {
                if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
                    Piece* targetedPiece = board.getPieceAt(newX, newY);
                    // Empty space, add move
                    if (targetedPiece == nullptr) {
                        moves.emplace_back(x, y, newX, newY, nullptr);
                    // Opponent's piece, add capture and stop
                    } else if (targetedPiece->getIsWhite() != isWhite) {
                        moves.emplace_back(x, y, newX, newY, targetedPiece);
                    }
                }
            }
        }
    }
    // Check castling moves
    if (canCastle(board)) {
        if (castleKingSide(board)) {
            moves.emplace_back(x, y, x + 2, y, nullptr); // Kingside castle
        }
        if (castleQueenSide(board)) {
            moves.emplace_back(x, y, x - 2, y, nullptr); // Queenside castle
        }
    }

    // Return list of valid moves
    return moves;
}

// King is not swappable
bool King::isSwappable(bool isWhite) { return false; }

// Mark that the King has made its first move
void King::doFirstMove() {
    firstMove = false;
    if (!firstMove) {}
    return;
}

// Check if castling is possible
bool King::canCastle(Board& board) {
    if (!firstMove) {
        return false;
    }
    return true;
}

// Check if Kingside castling is possible
bool King::castleKingSide(Board& board) {
    if (!canCastle(board)) {
        return false;
    }
    // Ensure the squares between King and Rook are empty
    if (board.getPieceAt(x + 1, y) != nullptr || board.getPieceAt(x + 2, y) != nullptr) {
        return false;
    }
    // Check if the Rook is in the right position and hasn't moved
    Piece* piece = board.getPieceAt(x + 3, y); 
    Rook* rook = dynamic_cast<Rook*>(piece);
    if (rook == nullptr || !rook->getFirstMove() || rook->getName() != "Rook") {
        return false;
    }
    return true; 
}

// Check if Queenside castling is possible
bool King::castleQueenSide(Board& board) {
    if (!canCastle(board)) {
        return false;
    }
    // Ensure the squares between King and Rook are empty
    if (board.getPieceAt(x - 1, y) != nullptr || board.getPieceAt(x - 2, y) != nullptr || board.getPieceAt(x - 3, y) != nullptr) {
        return false;
    }
    // Check if the Rook is in the correct position and hasn't moved
    Piece* piece = board.getPieceAt(x - 4, y); 
    Rook* rook = dynamic_cast<Rook*>(piece);
    if (rook == nullptr || !rook->getFirstMove() || rook->getName() != "Rook") {
        return false;
    }
    return true;
}
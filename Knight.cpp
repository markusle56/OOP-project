#include "Knight.h"
#include "Board.h"
#include "iostream"

// Knight constructor, initializes Knight with texture based on color
Knight::Knight(bool isWhite, int x, int y) : Piece(isWhite, x, y) {
    name = "Knight";
    if(isWhite) {
        textureFilePath = "IMG/Knight_W.png";
    } else {
        textureFilePath = "IMG/Knight_B.png";
    }
    if (!texture.loadFromFile(textureFilePath))
    {
        std::cout << "ERROR.....Could not load the Knight image" << std::endl;
    }
    sprite.setTexture(texture);
}

// Draw the Knight on the board
void Knight::draw(sf::RenderWindow &window ) {
    sprite.setScale(0.15, 0.15); // Scale image
    this->setPosition(x, y); // Position the Knight
    window.draw(sprite); // Render it
}

// Get possible moves for the Knight
std::vector<Move> Knight::getPossibleMoves(Board& board) {
    std::vector<Move> moves;

    // Define all possible Knight moves (L-shape)
    int moveSet[8][2] = {{2, 1}, {2, -1}, {-2, -1}, {-2, 1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
    // Check each possible move
    for (int i = 0; i < 8; i++) {
        int newX = x + moveSet[i][0];
        int newY = y + moveSet[i][1];
        // Ensure new position is within the board
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

    // Return list of valid moves
    return moves;
}

// Check if the Knight can be swapped based on color
bool Knight::isSwappable(bool isWhite) {
    if (this->isWhite == isWhite) {
        return true;
    }
    return false;
}
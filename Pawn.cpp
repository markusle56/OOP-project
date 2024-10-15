#include "Pawn.h"
#include "Board.h"
#include "iostream"

// Pawn constructor, initializes Pawn with texture based on color
Pawn::Pawn(bool isWhite, int x, int y): Piece(isWhite, x,y), firstMove(true){
    name = "Pawn";
    if(isWhite) {
        textureFilePath = "IMG/Pawn_W.png";
    } else {
        textureFilePath = "IMG/Pawn_B.png";
    }
    if (!texture.loadFromFile(textureFilePath))
    {
        std::cout << "ERROR.....Could not load the Pawn image" << std::endl;
    }
    sprite.setTexture(texture);
}

// Draw the Pawn on the board
void Pawn::draw(sf::RenderWindow& window) {
    sprite.setScale(0.15, 0.15); // Scale image
    this->setPosition(x, y); // Position the Pawn
    window.draw(sprite); // Render it
}

// Get possible moves for the Pawn
std::vector<Move> Pawn::getPossibleMoves(Board& board) {
    std::vector<Move> moves;

    // Define all possible Pawn moves
    int direction; 
    if (isWhite) {
        direction = -1;
    } else {
        direction = 1; 
    }
    int newY = y + direction;
    // Ensure new position is within the board
    if (newY >= 0 && newY < 8) {
        Piece* targetedPiece = board.getPieceAt(x, newY);
        // Empty space, add move
        if (targetedPiece == nullptr) {
            moves.emplace_back(x, y, x, newY, nullptr);
            // Move two squares forward on first move 
            if (firstMove == true && board.getPieceAt(x, newY + direction) == nullptr) {
                moves.emplace_back(x, y, x, newY + direction, nullptr);
            }
        }
    }
    // Capture diagonally to the right
    if (x + 1 <= 7 && board.getPieceAt(x + 1, newY) && board.getPieceAt(x + 1, newY)->getIsWhite() != isWhite) {
        moves.emplace_back(x, y, x + 1, newY, board.getPieceAt(x + 1, newY));
    } 
    // Capture diagonally to the left
    if (x - 1 >= 0 && board.getPieceAt(x - 1, newY) && board.getPieceAt(x - 1, newY)->getIsWhite() != isWhite) {
        moves.emplace_back(x, y, x - 1, newY, board.getPieceAt(x - 1, newY));
    }
    
    // Return possible moves
    return moves;
}

// Check if the Pawn can be swapped based on color
bool Pawn::isSwappable(bool isWhite) { 
    if (this->isWhite == isWhite) {
        return true;
    }
    return false;
}

// Mark that the Pawn has made its first move
void Pawn::doFirstMove() {
    firstMove = false;
    if (!firstMove) {}
    return;
}
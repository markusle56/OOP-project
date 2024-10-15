#include "Board.h"
#include "Pawn.h"
#include "Rook.h"
#include "King.h"
#include "Move.h"
#include <iostream>

void testBoardSetup() {
    Board board;
    board.setupBoard(); // Set up a standard board
    Piece* pawn = board.getPieceAt(1, 1); // White pawn at (1, 1)
    if (pawn != nullptr && pawn->getName() == "Pawn") {
        std::cout << "Board Setup Test: PASSED\n";
    } else {
        std::cout << "Board Setup Test: FAILED\n";
    }
}

void testBoardMovePiece() {
    Board board;
    board.setupBoard();
    Pawn pawn(true, 2, 2); // White pawn
    Move move(3, 1, 3, 3, nullptr);
    board.movePiece(move); 
    Piece * piece = board.getPieceAt(3,3);
    Piece * pieceNull = board.getPieceAt(3,1);
    if (piece && piece->getName() == "Pawn" && pieceNull == nullptr ) {
        std::cout << "Board Move Piece Test: PASSED\n";
    } else {
        std::cout << "Board Move Piece Test: FAILED\n";
    }
}

int main() {
    testBoardSetup();
    testBoardMovePiece();
    return 0;
}

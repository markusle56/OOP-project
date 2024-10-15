#include "Bishop.h"
#include "Board.h"
#include <iostream>

void testBishopConstructor() {
    Bishop bishop(true, 2, 0); // White bishop at (2, 0)
    if (bishop.getX() == 2 && bishop.getY() == 0 && bishop.getIsWhite()) {
        std::cout << "Bishop Constructor Test: PASSED\n";
    } else {
        std::cout << "Bishop Constructor Test: FAILED\n";
    }
}

void testBishopDiagonalMoves() {
    Board board;
    Bishop bishop(true, 2, 0); // White bishop
    std::vector<Move> moves = bishop.getPossibleMoves(board);
    if (!moves.empty()) { // Bishop should have diagonal moves available
        std::cout << "Bishop Diagonal Moves Test: PASSED\n";
    } else {
        std::cout << "Bishop Diagonal Moves Test: FAILED\n";
    }
}

void testBishopBlockedMove() {
    Board board;
    board.setupBoard();
    Bishop bishop(true, 2, 0);
    std::vector<Move> moves = bishop.getPossibleMoves(board);
    bool blocked = true;
    for (Move move : moves) {
        if (move.endX == 4 && move.endY == 2) {
            blocked = false; // Should not be able to move beyond the blocking pawn
        }
    }

    if (blocked) {
        std::cout << "Bishop Blocked Move Test: PASSED\n";
    } else {
        std::cout << "Bishop Blocked Move Test: FAILED\n";
    }
}

void testBishopCapture() {
    Board board;
    Bishop bishop(true, 2, 0);
    Pawn blackPawn(false, 4, 2); // Opponent's pawn to capture
    std::vector<Move> moves = bishop.getPossibleMoves(board);
    bool canCapture = false;
    for (Move move : moves) {
        if (move.endX == 4 && move.endY == 2) {
            canCapture = true;
        }
    }

    if (canCapture) {
        std::cout << "Bishop Capture Test: PASSED\n";
    } else {
        std::cout << "Bishop Capture Test: FAILED\n";
    }
}

int main() {
    testBishopConstructor();
    testBishopDiagonalMoves();
    testBishopBlockedMove();
    testBishopCapture();
    return 0;
}

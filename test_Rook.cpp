#include "Rook.h"
#include "Board.h"
#include <iostream>

void testRookConstructor() {
    Rook rook(true, 0, 0); // White rook at (0, 0)
    if (rook.getX() == 0 && rook.getY() == 0 && rook.getIsWhite()) {
        std::cout << "Rook Constructor Test: PASSED\n";
    } else {
        std::cout << "Rook Constructor Test: FAILED\n";
    }
}

void testRookMoveHorizontal() {
    Board board;
    Rook rook(true, 0, 0); // White rook
    std::vector<Move> moves = rook.getPossibleMoves(board);
    if (moves.size() > 0) { // Rook should have valid horizontal and vertical moves
        std::cout << "Rook Move Horizontal Test: PASSED\n";
    } else {
        std::cout << "Rook Move Horizontal Test: FAILED\n";
    }
}

void testRookCapture() {
    Board board;
    board.setupBoard();
    Rook rook(true, 3, 3); // White rook
    std::vector<Move> moves = rook.getPossibleMoves(board);
    bool canCapture = false;
    for (Move move : moves) {
        if (move.endX == 3 && move.endY == 1) {
            canCapture = true; // Rook should be able to capture
        }
    }
    if (canCapture) {
        std::cout << "Rook Capture Test: PASSED\n";
    } else {
        std::cout << "Rook Capture Test: FAILED\n";
    }
}

int main() {
    testRookConstructor();
    testRookMoveHorizontal();
    testRookCapture();
    return 0;
}

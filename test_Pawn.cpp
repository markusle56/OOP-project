#include "Pawn.h"
#include "Board.h"
#include <iostream>

void testPawnConstructor() {
    Pawn pawn(true, 1, 1); // White pawn at (1, 1)
    if (pawn.getX() == 1 && pawn.getY() == 1 && pawn.getIsWhite()) {
        std::cout << "Pawn Constructor Test: PASSED\n";
    } else {
        std::cout << "Pawn Constructor Test: FAILED\n";
    }
}

void testPawnMoveForward() {
    Board board;
    Pawn pawn(true, 3, 3);
    std::vector<Move> moves = pawn.getPossibleMoves(board);
    if (moves.size() == 2) { // On first move, pawn can move 1 or 2 squares forward
        std::cout << "Pawn Move Forward Test: PASSED\n";
    } else {
        std::cout << "Pawn Move Forward Test: FAILED\n";
    }
}

void testPawnInvalidCapture() {
    Board board;
    board.setupBoard();
    Pawn pawn(true, 2, 2); // White pawn at (2, 2)
    std::vector<Move> moves = pawn.getPossibleMoves(board);
    bool invalidCapture = true;
    for (Move move : moves) {
        if (move.endX == 2 && move.endY == 1) {
            invalidCapture = false; // Capture should not be possible
        }
    }
    if (invalidCapture) {
        std::cout << "Pawn Invalid Capture Test: PASSED\n";
    } else {
        std::cout << "Pawn Invalid Capture Test: FAILED\n";
    }
}

void testPawnPromotion() {
    Board board;
    Pawn pawn(true, 1, 1); // Pawn on the 7th rank
    std::vector<Move> moves = pawn.getPossibleMoves(board);
    for (Move move : moves) {
        if (move.endY == 0) { // Check if move results in promotion
            std::cout << "Pawn Promotion Test: PASSED\n";
            return;
        }
    }
    std::cout << "Pawn Promotion Test: FAILED\n";
}

int main() {
    testPawnConstructor();
    testPawnMoveForward();
    testPawnInvalidCapture();
    testPawnPromotion();
    return 0;
}

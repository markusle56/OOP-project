#include "Move.h"
#include "Piece.h"
#include "Pawn.h"
#include <iostream>

void testMoveConstructor() {
    Piece* capturedPiece = nullptr; // No captured piece in this move
    Move move(1, 1, 3, 3, capturedPiece); // Move from (1, 1) to (3, 3)

    if (move.startX == 1 && move.startY == 1 && move.endX == 3 && move.endY == 3 && move.captured_piece == nullptr) {
        std::cout << "Move Constructor Test: PASSED\n";
    } else {
        std::cout << "Move Constructor Test: FAILED\n";
    }
}

void testMoveWithCapture() {
    // Simulate a piece being captured
    Piece capturedPiece(true, 3, 3); // Assume a white piece at (3, 3)
    Move move(1, 1, 3, 3, &capturedPiece); // Move that captures a piece

    if (move.captured_piece == &capturedPiece) {
        std::cout << "Move With Capture Test: PASSED\n";
    } else {
        std::cout << "Move With Capture Test: FAILED\n";
    }
}

void testMoveTargeting() {
    Piece king(true, 4, 4); // White king at (4, 4)
    Move move(1, 1, 4, 4, nullptr); // Move to target the king's position

    if (move.isTargeted(&king)) {
        std::cout << "Move Targeting Test: PASSED\n";
    } else {
        std::cout << "Move Targeting Test: FAILED\n";
    }
}

int main() {
    testMoveConstructor();
    testMoveWithCapture();
    testMoveTargeting();
    return 0;
}

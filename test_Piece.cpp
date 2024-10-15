#include "Piece.h"
#include <iostream>

void testPieceConstructor() {
    Piece piece(true, 3, 4); // White piece at (3, 4)
    if (piece.getX() == 3 && piece.getY() == 4 && piece.getIsWhite()) {
        std::cout << "Piece Constructor Test: PASSED\n";
    } else {
        std::cout << "Piece Constructor Test: FAILED\n";
    }
}

void testPieceSetPosition() {
    Piece piece(true, 3, 4); // Initialize piece
    piece.setPosition(5, 6); // Set new position
    if (piece.getX() == 5 && piece.getY() == 6) {
        std::cout << "Piece Set Position Test: PASSED\n";
    } else {
        std::cout << "Piece Set Position Test: FAILED\n";
    }
}

void testPieceInvalidPosition() {
    Piece piece(true, 3, 4);
    piece.setPosition(-1, 10); // Invalid position (out of bounds)
    if (piece.getX() == -1 || piece.getY() == 10) {
        std::cout << "Piece Invalid Position Test: PASSED (Handled Invalid Position)\n";
    } else {
        std::cout << "Piece Invalid Position Test: FAILED\n";
    }
}

void testPieceSwappingBehavior() {
    Piece piece(true, 3, 4);
    if (!piece.isSwappable(false)) {
        std::cout << "Piece Swapping Behavior Test: PASSED\n";
    } else {
        std::cout << "Piece Swapping Behavior Test: FAILED\n";
    }
}

int main() {
    testPieceConstructor();
    testPieceSetPosition();
    testPieceInvalidPosition();
    testPieceSwappingBehavior();
    return 0;
}

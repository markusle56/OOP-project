#include "King.h"
#include "Rook.h"
#include "Board.h"
#include <iostream>

void testKingConstructor() {
    King king(true, 4, 0); // White king at (4, 0)
    if (king.getX() == 4 && king.getY() == 0 && king.getIsWhite()) {
        std::cout << "King Constructor Test: PASSED\n";
    } else {
        std::cout << "King Constructor Test: FAILED\n";
    }
}

void testKingMovement() {
    Board board;
    King king(true, 4, 0); // White king at (4, 0)
    std::vector<Move> moves = king.getPossibleMoves(board);
    std::cout << moves.size();
    if (moves.size() == 5) { // King should move one step in any direction
        std::cout << "King Movement Test: PASSED\n";
    } else {
        std::cout << "King Movement Test: FAILED\n";
    }
}


void testBlockedCastling() {
    Board board;
    board.setupBoard();
    King king(true, 4, 7); // King at original position
    std::vector<Move> moves = king.getPossibleMoves(board);
    bool canCastle = false;
    for (Move move : moves) {
        if (move.endX == 6 && move.endY == 7) {
            canCastle = true; // Castling should be blocked
        }
    }

    if (!canCastle) {
        std::cout << "Blocked Castling Test: PASSED\n";
    } else {
        std::cout << "Blocked Castling Test: FAILED\n";
    }
}

int main() {
    testKingConstructor();
    testKingMovement();
    testBlockedCastling();
    return 0;
}

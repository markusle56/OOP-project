#include "Queen.h"
#include "Board.h"
#include <iostream>

void testQueenConstructor() {
    Queen queen(true, 3, 0); // White queen at (3, 0)
    if (queen.getX() == 3 && queen.getY() == 0 && queen.getIsWhite()) {
        std::cout << "Queen Constructor Test: PASSED\n";
    } else {
        std::cout << "Queen Constructor Test: FAILED\n";
    }
}

void testQueenAllMoves() {
    Board board;
    Queen queen(true, 3, 3); // White queen in the middle of the board
    std::vector<Move> moves = queen.getPossibleMoves(board);
    if (!moves.empty()) { // Queen should have diagonal, horizontal, and vertical moves
        std::cout << "Queen All Moves Test: PASSED\n";
    } else {
        std::cout << "Queen All Moves Test: FAILED\n";
    }
}

void testQueenCapture() {
    Board board;
    board.setupBoard();
    Queen queen(true, 3, 3); // White queen
    Pawn blackPawn(false, 5, 5); // Black pawn to capture
    std::vector<Move> moves = queen.getPossibleMoves(board);
    bool canCapture = false;
    for (Move move : moves) {
        if (move.endX == 5 && move.endY == 1) {
            canCapture = true;
        }
    }

    if (canCapture) {
        std::cout << "Queen Capture Test: PASSED\n";
    } else {
        std::cout << "Queen Capture Test: FAILED\n";
    }
}

void testQueenBlockedMove() {
    Board board;
    board.setupBoard();
    Queen queen(true, 2, 3);
    std::vector<Move> moves = queen.getPossibleMoves(board);
    bool blocked = true;
    for (Move move : moves) {
        if (move.endX == 5 && move.endY == 0) {
            blocked = false; // Move should not pass the blocking pawn
        }
    }

    if (blocked) {
        std::cout << "Queen Blocked Move Test: PASSED\n";
    } else {
        std::cout << "Queen Blocked Move Test: FAILED\n";
    }
}

int main() {
    testQueenConstructor();
    testQueenAllMoves();
    testQueenCapture();
    testQueenBlockedMove();
    return 0;
}

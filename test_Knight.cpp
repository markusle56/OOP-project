#include "Knight.h"
#include "Board.h"
#include <iostream>

void testKnightConstructor() {
    Knight knight(true, 1, 0); // White knight
    if (knight.getX() == 1 && knight.getY() == 0 && knight.getIsWhite()) {
        std::cout << "Knight Constructor Test: PASSED\n";
    } else {
        std::cout << "Knight Constructor Test: FAILED\n";
    }
}

void testKnightLShapedMoves() {
    Board board;
    Knight knight(true, 1, 0); // White knight
    std::vector<Move> moves = knight.getPossibleMoves(board);
    if (moves.size() == 3) { // Knight should have 2 valid L-shaped moves initially
        std::cout << "Knight L-Shaped Moves Test: PASSED\n";
    } else {
        std::cout << "Knight L-Shaped Moves Test: FAILED\n";
    }
}

void testKnightOutOfBoundsMove() {
    Board board;
    Knight knight(true, 0, 0); // Knight at corner
    std::vector<Move> moves = knight.getPossibleMoves(board);
    bool outOfBoundsMove = false;
    for (Move move : moves) {
        if (move.endX < 0 || move.endY < 0 || move.endX >= 8 || move.endY >= 8) {
            outOfBoundsMove = true;
        }
    }
    if (!outOfBoundsMove) {
        std::cout << "Knight Out Of Bounds Move Test: PASSED\n";
    } else {
        std::cout << "Knight Out Of Bounds Move Test: FAILED\n";
    }
}

void testKnightCapture() {
    Board board;
    board.setupBoard();
    Knight knight(true, 3, 3); // White knight
    std::vector<Move> moves = knight.getPossibleMoves(board);
    bool canCapture = false;
    for (Move move : moves) {
        if (move.endX == 2 && move.endY == 1) {
            canCapture = true;
        }
    }
    if (canCapture) {
        std::cout << "Knight Capture Test: PASSED\n";
    } else {
        std::cout << "Knight Capture Test: FAILED\n";
    }
}

int main() {
    testKnightConstructor();
    testKnightLShapedMoves();
    testKnightOutOfBoundsMove();
    testKnightCapture();
    return 0;
}

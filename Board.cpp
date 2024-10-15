#include "Board.h"
#include <iostream>

Board::Board() {   
    textureFilePath = "IMG/Board.png";
    // Initialize board array to nullptr
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            board[i][j] = nullptr;
        }   
    }
    // Load board texture
    if (!texture.loadFromFile(textureFilePath)) {
        std::cout << "ERROR.....Could not load the board" << std::endl;
    }
    sprite.setTexture(texture);
}

Board::~Board() {
    // Clean up dynamically allocated pieces
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if (board[i][j] != nullptr) {
                delete board[i][j];
            }
        }
    }
}

void Board::drawBoard(sf::RenderWindow& window) {   
    // Scale the board sprite to fit the window
    sprite.setScale(0.74074, 0.74074);
    window.draw(sprite); // Draw the board
    // Draw the pieces on the board
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if (board[i][j] != nullptr) { // If there's a piece on the board at [i][j]
                board[i][j]->draw(window); // Draw the piece
            }
        }
    }
}

void Board::drawPieces(sf::RenderWindow& window) {
    // Draw each piece on the board
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if (board[i][j] != nullptr) {  // If there's a piece on the board at [i][j]
                board[i][j]->draw(window); // Draw the piece
            }
        }
    }
}

void Board::setupBoard() {
    // Initialize the board with no pieces (nullptr)
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = nullptr; 
        }
    }
    // Set up pawns
    for (int i = 0; i < 8; i++) {
        board[i][1] = new Pawn(false, i, 1);  // Black pawns
        board[i][6] = new Pawn(true, i, 6);   // White pawns
    }
    // Set up rooks, knights, and bishops
    int temp[] = {0, 7};  // Positions for back row pieces (0 for black, 7 for white)
    for (int i = 0; i < 2; i++) {
        board[0][temp[i]] = new Rook(i, 0, temp[i]); // Rooks
        board[7][temp[i]] = new Rook(i, 7, temp[i]);
        board[1][temp[i]] = new Knight(i, 1, temp[i]); // Knights
        board[6][temp[i]] = new Knight(i, 6, temp[i]);
        board[2][temp[i]] = new Bishop(i, 2, temp[i]); // Bishops
        board[5][temp[i]] = new Bishop(i, 5, temp[i]);
        board[3][temp[i]] = new Queen(i, 3, temp[i]); // Queen
        board[4][temp[i]] = new King(i, 4, temp[i]); // King
    }
    display(0,0,1);
}

Piece* Board::getPieceAt(int x, int y) {
    return board[x][y]; // Return piece at (x, y)
}

void Board::movePiece(const Move& move) {
    Piece* piece = board[move.startX][move.startY]; // Get piece at start position
    if (piece) {
        display(move.startX,move.startY, 3);
        display(move.endX, move.endY, 4);
        board[move.endX][move.endY] = piece; // Move piece to end position
        board[move.startX][move.startY] = nullptr; // Clear start position
        piece->setPosition(move.endX, move.endY); // Update piece position
        piece->doFirstMove(); // Mark piece's first move
        move_history.push_back(move); // Add move to history
        // Handle castling
        if (piece->getName() == "King" && abs(piece->getX() - move.startX) == 2) {
            if (piece->getX() > move.startX) { // King-side castle
                Piece* rook = board[7][move.startY]; // Get king-side rook
                if (rook && rook->getName() == "Rook") {
                    // Move rook next to king
                    board[5][move.startY] = rook; 
                    board[5][move.startY] = rook; 
                    board[7][move.startY] = nullptr;
                    rook->setPosition(5, move.startY);
                }
            } else if (piece->getX() < move.startX) { // Queen-side castle
                Piece* rook = board[0][move.startY]; // Get queen-side rook
                if (rook && rook->getName() == "Rook") {
                    // Move rook next to king
                    board[3][move.startY] = rook; 
                    board[0][move.startY] = nullptr;
                    rook->setPosition(3, move.startY);
                }
            }
            display(0, 0, 2);
        }
        // Handle piece swap after capture
        if (move.captured_piece != nullptr && piece->isSwappable(piece->getIsWhite())) {
            this->swap(piece); // Swap if needed
        }
        display(move.endX, move.endY, 5);
    }
    return;
}

sf::Vector2i Board::isCheck(bool isWhite) {
    Piece * piece = nullptr;
    Piece * king = nullptr;
    std::vector<Move> possibleMoves; 

    // Iterate through the board to find all enemy pieces and the king
    for (int i = 0; i < 8; i++) { 
        for (int j = 0; j < 8; j++) {
            piece = board[i][j];
            // Collect possible moves for enemy pieces
            if (piece && piece->getIsWhite() != isWhite) {
                std::vector<Move> pieceMoves = piece->getPossibleMoves(*this);
                possibleMoves.insert(possibleMoves.end(), pieceMoves.begin(), pieceMoves.end());
            }
            // Identify the king of the current player
            if (piece && piece->getName() == "King" && piece->getIsWhite() == isWhite) {
                king = piece;
            }
        }
    }
    // If no king is found, return special value (-2, -2)
    if (!king) {
        return sf::Vector2i(-2, -2);
    }
    // Check if any move targets the king
    for (auto move : possibleMoves) {
        if (move.isTargeted(king)) {
            return sf::Vector2i(king->getX(), king->getY()); // Return king's position if in check
        }
    }
    return sf::Vector2i(-1, -1); // Return (-1, -1) if the king is not in check
}

void Board::swap(Piece *piece) {
    if (piece == nullptr) {
        return; // Return if the piece is null
    }
    std::vector<sf::Vector2i> swappablePiece;
    // Find all swappable pieces on the board
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece* currentPiece = board[i][j];
            if (currentPiece && currentPiece->isSwappable(piece->getIsWhite()) && currentPiece != piece) {
                swappablePiece.push_back(currentPiece->getPosition()); // Add to swappable list
            }
        }
    }
    // If no swappable pieces, return
    if (swappablePiece.size() < 1) {
        return;
    }
    // Randomly select a swappable piece
    srand(time(0));
    int randNum = rand() % swappablePiece.size();
    sf::Vector2i swappedPiece = swappablePiece[randNum];
    // Swap positions of the two pieces
    board[piece->getX()][piece->getY()] = board[swappedPiece.x][swappedPiece.y];
    board[piece->getX()][piece->getY()]->setPosition(piece->getX(), piece->getY());
    board[swappedPiece.x][swappedPiece.y] = piece;
    board[swappedPiece.x][swappedPiece.y]->setPosition(swappedPiece.x, swappedPiece.y);

    return; 
}

Piece* Board::canPromote() {
    Piece* piece = nullptr;
    // Iterate through the board to find pawns eligible for promotion
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            piece = board[i][j];
            if (piece && piece->getName() == "Pawn") { // Check if the piece is a pawn
                // White pawn promotion at the top row
                if (piece->getY() == 0 && piece->getIsWhite()) {
                    return piece; // Return the pawn ready for promotion
                }
                // Black pawn promotion at the bottom row
                if (piece->getY() == 7 && !piece->getIsWhite()) {
                    return piece; // Return the pawn ready for promotion
                }
            }
        }
    }
    return nullptr; // No pawn found for promotion
}

bool Board::promote(Piece* piece, std::string intoPiece) {
    // Promote the pawn to the chosen piece
    if (intoPiece == "Queen") {
        board[piece->getX()][piece->getY()] = new Queen(piece->getIsWhite(), piece->getX(), piece->getY()); // Promote to Queen
        delete piece; // Delete the old pawn
    } else if (intoPiece == "Rook") {
        board[piece->getX()][piece->getY()] = new Rook(piece->getIsWhite(), piece->getX(), piece->getY()); // Promote to Rook
        delete piece;
    } else if (intoPiece == "Knight") {
        board[piece->getX()][piece->getY()] = new Knight(piece->getIsWhite(), piece->getX(), piece->getY()); // Promote to Knight
        delete piece;
    } else if (intoPiece == "Bishop") {
        board[piece->getX()][piece->getY()] = new Bishop(piece->getIsWhite(), piece->getX(), piece->getY()); // Promote to Bishop
        delete piece;
    }
    return false; // Return false indicating the promotion was handled
}

void Board::display(int x, int y, int code) {
    if (code == 1) {
        std::cout << "Successfully set up the board." << std::endl;
    } else if (code == 2) {
        std::cout << "CASTLING" << std::endl;
    } else if (code == 3) {
        std::string name = board[x][y]->getName();
        std::cout << name << " has moved from (" << x << "," << y << ") to ";
    } else if (code == 4) {
        std::cout << "(" << x << "," << y << ")";
    } else if (code == 5) {
        std::string name = board[x][y]->getName();
        std::cout << " and swap into " << name << "." << std::endl;
    }
}
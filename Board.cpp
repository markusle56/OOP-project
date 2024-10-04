#include "Board.h"
#include <iostream>

Board::Board()
{   
    textureFilePath = "IMG/Board.png";
    // Initialize board array to nullptr
    for(int i = 0; i < 8; ++i)
        for(int j = 0; j < 8; ++j)
            board[i][j] = nullptr;
    
    // Load board texture
    if (!texture.loadFromFile(textureFilePath))
    {
        
    }
    sprite.setTexture(texture);
}

Board::~Board()
{
    // Clean up dynamically allocated pieces
    for(int i = 0; i < 8; ++i) 
        for(int j = 0; j < 8; ++j)
            if(board[i][j] != nullptr)
                delete board[i][j];
}

void Board::draw(sf::RenderWindow& window)
{   
    sprite.setScale(0.74074,0.74074);
    window.draw(sprite);
    
    for(int i = 0; i < 8; ++i)
        for(int j = 0; j < 8; ++j)
            if(board[i][j] != nullptr)
               board[i][j]->draw(window);
}

void Board::setupBoard() {
    for (int i = 0; i < 8; i++) {
        board[i][1] = new Pawn(false, i, 1);
        board[i][6] = new Pawn(true, i, 6);
    }
    int temp[] = {0,7};
    for (int i = 0; i < 2; i++) {
            board[0][temp[i]] = new Brook(i, 0, temp[i]);
            board[7][temp[i]] = new Brook(i, 7, temp[i]);
            // board[temp[i]][1] = new Knight(i,temp[i],1);
            // board[temp[i]][6] = new Knight(i,temp[i],6);
            board[2][temp[i]] = new Bishop(i,2,temp[i]);
            board[5][temp[i]] = new Bishop(i,5,temp[i]);
            // need to covert
    }
    board[3][0] = new Queen(false,3,0);
    board[4][0] = new King(false,4,0);
    board[3][7] = new King(true, 3,7);
    board[4][7] = new Queen(true,4,7);    
}

Piece* Board::getPieceAt(int x, int y) {
    return board[x][y];
}

void Board::movePiece(const Move& move) {
    Piece* piece = board[move.startX][move.startY];
    if(piece)
    {
        board[move.endX][move.endY] = piece;
        board[move.startX][move.startY] = nullptr;
        piece->setPosition(move.endX, move.endY);
        piece->doFirstMove();
        move_history.push_back(move);
        if (move.captured_piece != nullptr && piece->isSwappable(piece->getIsWhite())) {
            this->swap(piece);
        }

    }
    return;
}

bool Board::isCheck(bool isWhite) {

    Piece * piece = nullptr;
    Piece * king = nullptr;
    std::vector<Move> possibleMoves; 
    for (int i = 0; i < 8; i++) { 
        for (int j = 0; j < 8; j++) {
            piece = board[i][j];
            if (piece && piece->getIsWhite() == isWhite) {
                std::vector<Move> pieceMoves = piece->getPossibleMoves(*this);
                possibleMoves.insert(possibleMoves.end(), pieceMoves.begin(), pieceMoves.end());
            }
            if (piece && piece->isKing(!isWhite)) {
                king = piece;
            }
        }
    }
    for (auto move: possibleMoves) {
        if(move.isTargeted(king)) {
            return true;
        }
    }
    return false;
}

void Board::swap(Piece *piece) {
    if (piece == nullptr) {
        return;
    }
    std::vector<sf::Vector2i> swappablePiece;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece* currentPiece = board[i][j];
            if (currentPiece && currentPiece->isSwappable(piece->getIsWhite()) && currentPiece != piece) {
                swappablePiece.push_back(currentPiece->getPosition());
            }
        }
    }
    if (swappablePiece.size() < 1 ) {
        return;
    }
    srand(time(0));
    int randNum = rand() % swappablePiece.size();
    sf::Vector2i swappedPiece = swappablePiece[randNum];
    board[piece->getX()][piece->getY()] = board[swappedPiece.x][swappedPiece.y];
    board[piece->getX()][piece->getY()]->setPosition(piece->getX(),piece->getY());
    board[swappedPiece.x][swappedPiece.y] = piece;
    board[swappedPiece.x][swappedPiece.y]->setPosition(swappedPiece.x, swappedPiece.y);

    return; 

}
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
            // board[temp[i]][0] = new Brook(i, temp[i],0);
            // board[temp[i]][7] = new Brook(i,temp[i],7);
            // board[temp[i]][1] = new Knight(i,temp[i],1);
            // board[temp[i]][6] = new Knight(i,temp[i],6);
            // board[temp[i]][2] = new Bishop(i,temp[i],2);
            // board[temp[i]][5] = new Bishop(i,temp[i],5);
            // need to covert
    }
    // board[0][3] = new Queen(false,0,3);
    // board[0][4] = new King(false,0,4);
    // board[7][3] = new King(true, 7,3);
    // board[7][4] = new Queen(true, 7,4);    
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
        if (move.captured_piece != nullptr) {
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
            if (board[i][j] && board[i][j]->isSwappable(piece->getIsWhite()) && board[i][j] != piece) {
                swappablePiece.push_back(board[i][j]->getPosition());
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
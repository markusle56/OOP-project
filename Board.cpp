#include "Board.h"

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
    sprite.setScale(0.9259,0.9259);
    window.draw(sprite);
    board[1][1]->draw(window);
    // Draw all pieces
    // for(int i = 0; i < 8; ++i)
    //     for(int j = 0; j < 8; ++j)
    //         if(board[i][j] != nullptr)
               ///board[i][j]->draw(window);
}

void Board::setupBoard() {
    for (int i = 0; i < 8; i++) {
        board[1][i] = new Pawn(false, 1, i);
        board[6][i] = new Pawn(true, 6, i);
    }
    int temp[] = {0,7};
    for (int i = 0; i < 2; i++) {
            // board[temp[i]][0] = new Brook(i, temp[i],0);
            // board[temp[i]][7] = new Brook(i,temp[i],7);
            // board[temp[i]][1] = new Knight(i,temp[i],1);
            // board[temp[i]][6] = new Knight(i,temp[i],6);
            // board[temp[i]][2] = new Bishop(i,temp[i],2);
            // board[temp[i]][5] = new Bishop(i,temp[i],5);
    }
    // board[0][3] = new Queen(false,0,3);
    // board[0][4] = new King(false,0,4);
    // board[7][3] = new King(true, 7,3);
    // board[7][4] = new Queen(true, 7,4);    
}
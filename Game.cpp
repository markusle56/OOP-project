#include "Game.h"

Game::Game(): window(sf::VideoMode(800,800), "Maj Chess"), isWhiteTurn(true), gameOver(false), selectedPiece(nullptr){
};

Game::~Game() {}

void Game::init()
{
    board.setupBoard();
}

void Game::run()
{
    while (window.isOpen())
    {
        handleInput();
        update();
        render();
    }
}

void Game::handleInput()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed) {
            window.close();
        }
       
        if(event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left) {
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;
                int X = mouseX / 100;
                int Y = mouseY / 100;
                if (selectedPiece == nullptr) {
                    selectedPiece = board.getPieceAt(X,Y);
                    if (selectedPiece && selectedPiece->getIsWhite() == isWhiteTurn) {
                        possibleMoves = selectedPiece->getPossibleMoves(board);
                    } else {
                        selectedPiece = nullptr;
                    }
                } else {
                    if (selectedPiece->getX() == X &&  selectedPiece->getY() == Y) {
                        selectedPiece = nullptr;
                    } else {
                        for (auto & move : possibleMoves) {
                            if (move.endX == X && move.endY == Y) {
                                move.execute(board);
                                isWhiteTurn = !isWhiteTurn;
                                selectedPiece = nullptr;
                                break;
                            }
                        }
                    }
                    if (selectedPiece == nullptr) {
                        possibleMoves.clear();
                    }
                }
            }
        }
    }
}


void Game::update()
{   
    if (board.isCheck(isWhiteTurn)){
        std::cout<<"CHECK CHECK CHECK "<<std::endl;
    }

    if(gameOver) {
        return;
    }
}

void Game::render()
{
    window.clear(sf::Color::White);

    board.draw(window);
    for (auto move : possibleMoves) {
        move.draw(window);
    }
    window.display();
}
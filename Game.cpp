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
                std::cout<<"Click hear"<<X <<" x  is "<< Y << " y is "<<std::endl;
                if (selectedPiece == nullptr) {
                    std::cout<<"yes"<<std::endl;
                    selectedPiece = board.getPieceAt(X,Y);
                    if (selectedPiece && selectedPiece->getIsWhite() != isWhiteTurn) {
                        possibleMoves = selectedPiece->getPossibleMoves(board);
                        std::cout<<possibleMoves.size()<<std::endl;
                    }
                } else {
                    std::cout<<"no"<<std::endl;
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
                    possibleMoves.clear();
                }
            }
        }
    }
}


void Game::update()
{

    if(gameOver) {
        return;
    }
}

void Game::render()
{
    window.clear(sf::Color::White);

    for (auto move : possibleMoves) {
        move.draw(window);
    }


    board.draw(window);
    window.display();
}
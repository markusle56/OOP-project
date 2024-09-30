#include "Game.h"

Game::Game(): window(sf::VideoMode(800,800), "Maj Chess"), isWhiteTurn(true), gameOver(false) {};

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
    Piece * selectedPiece = nullptr;
    while (window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed) {
            window.close();
        }
       
        if(event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left) {
                int mouseX = event.mouseButton.x;
                int mosueY = event.mouseButton.y;
                int X = mouseX / 100;
                int Y = mosueY / 100;
                if (selectedPiece = nullptr) {
                    selectedPiece = board.getPieceAt(X,Y);
                    if (selectedPiece && selectedPiece->isW()== isWhiteTurn) {
                        possibleMoves = selectedPiece->getPossibleMoves(board);
                    }
                } else {
                    if (selectedPiece->getX() == X &&  selectedPiece->getY() == Y) {
                        selectedPiece = nullptr;
                    } else {
                        for (auto & move : possibleMoves) {
                            if (move.endX == X && move.endY == Y) {
                                move.execute(board);
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

    // draw higlighted of possible move

    board.draw(window);
    window.display();
}
#include "Game.h"

Game::Game(): window(sf::VideoMode(1000,1000), "Maj Chess"), isWhiteTurn(true), gameOver(false) {};

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
    board.draw(window);
    window.display();
}
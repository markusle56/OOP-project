#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Board.h"

class Game {
    private:
        Board board;
        bool isWhiteTurn;
        bool gameOver;
        sf::RenderWindow window;
    public:
        Game();
        ~Game();

        void init();
        void run();
        void render();
        void handleInput();
        void update();
};

#endif
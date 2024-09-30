#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Board.h"
#include <vector>
class Game {
    private:
        Board board;
        bool isWhiteTurn;
        bool gameOver;
        sf::RenderWindow window;
        std::vector<Move> possibleMoves;
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
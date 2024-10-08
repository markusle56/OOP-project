#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Board.h"
#include <vector>
#include <iostream>

class Game {
    private:
        Board board;
        bool isWhiteTurn;
        bool gameOver;
        sf::RenderWindow window;
        std::vector<Move> possibleMoves;
        Piece * selectedPiece;
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
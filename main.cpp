#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Piece.h"
#include "Pawn.h" 
#include "Move.h"
#include "Game.h"

int main()
{
    // Initialize the game and start the main loop
    Game game;
    game.init();
    game.run();

    return 0;
}

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Piece.h"
#include "Pawn.h" 
#include "Move.h"
#include "Game.h"

int main()
{
    Game game;
    game.init();
    game.run();


    return 0;
}

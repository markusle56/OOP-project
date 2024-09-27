#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Piece.h"
#include "Pawn.h" 

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1000,1000), "Maj Chess");

   
    Board board; 
    // Main loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the screen
        window.clear();

        board.setupBoard();
        board.draw(window);
        // Display the window contents
        window.display();
    }

    return 0;
}

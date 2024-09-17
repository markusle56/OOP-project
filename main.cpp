
#include <SFML/Graphics.hpp>

int main()
{
    // Create a window with the title "SFML Window"
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    // Create a circle shape with a radius of 50
    sf::CircleShape circle(50.0f);

    // Set the position of the circle (the center of the screen)
    circle.setPosition(375, 275); // Adjusted to center
    circle.setFillColor(sf::Color::Green); // Set the color of the circle

    // Main loop - runs until the window is closed
    while (window.isOpen())
    {
        // Event processing
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window if the close button is pressed
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window with a black color
        window.clear(sf::Color::Black);

        // Draw the circle
        window.draw(circle);

        // Display the contents of the window
        window.display();
    }

    return 0;
}

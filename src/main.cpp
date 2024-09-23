#include <iostream>
#include "entity.hpp"

#include <GLFW/glfw3.h>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

template<typename T>
T square(T x)
{
    return x * x;
}

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
 
        // Clear screen
        window.clear();
        // Update the window
        window.display();
    }
 
    return EXIT_SUCCESS;
}

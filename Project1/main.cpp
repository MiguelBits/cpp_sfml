#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <math.h>
#include <iostream>


int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

    }

    return 0;
}

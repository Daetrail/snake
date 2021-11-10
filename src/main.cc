#include "SFML/Graphics.hpp"

#include "Global.hh"

int main()
{
    sf::RenderWindow window(sf::VideoMode(G::WINDOW_WIDTH, G::WINDOW_HEIGHT), "Snake");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);



        window.display();
    }

    return 0;
}
#include "SFML/Graphics.hpp"

#include "Global.hh"
#include "Snake.hh"
#include "Game.hh"

int main()
{
    sf::RenderWindow window(sf::VideoMode(G::WINDOW_WIDTH, G::WINDOW_HEIGHT), "Snake", sf::Style::Close | sf::Style::Titlebar);

    Game game(G::SQUARE_SPACING, 0.1f, sf::Color::Blue, sf::Vector2f(G::WINDOW_WIDTH / 2.f - G::SQUARE_SPACING / 2, G::WINDOW_HEIGHT / 2.f - G::SQUARE_SPACING / 2), G::WINDOW_WIDTH, G::WINDOW_HEIGHT, sf::Color::Cyan);

    sf::Clock clock;
    float deltaTime;

    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        game.update(deltaTime);

        window.clear(sf::Color::Black);

        game.draw(window);

        window.display();
    }

    return 0;
}
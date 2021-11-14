#pragma once

#include <vector>

#include "SFML/Graphics.hpp"

#include "Snake.hh"
#include "Fruit.hh"

class Game
{
public:
    Game(const unsigned int& cellSpacing, const float& switchTime, const sf::Color& colour, const sf::Color& fruitColour, const sf::Vector2f& initialPosition, const unsigned int& WINDOW_WIDTH, const unsigned int& WINDOW_HEIGHT, const sf::Color& gridColour = sf::Color::White, const bool& grids = true);

    void eventLoop(sf::Event& event);

    void update(float& deltaTime);

    void draw(sf::RenderWindow& window);

private:
    Snake snake;
    Fruit fruit;

    bool grids = true;

    unsigned int cellSpacing;

    std::vector<sf::RectangleShape> horizontalLines;
    std::vector<sf::RectangleShape> verticalLines;    
    sf::Color gridColour;
};


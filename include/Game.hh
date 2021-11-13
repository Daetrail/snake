#pragma once

#include <vector>

#include "SFML/Graphics.hpp"

#include "Snake.hh"

class Game
{
public:
    Game(const unsigned int& cellSpacing, const float& switchTime, const sf::Color& colour, const sf::Vector2f& initialPosition, const unsigned int& WINDOW_WIDTH, const unsigned int& WINDOW_HEIGHT, const sf::Color& gridColour);

    void update(float& deltaTime);

    void draw(sf::RenderWindow& window);

private:
    Snake snake;

    unsigned int cellSpacing;

    std::vector<sf::RectangleShape> horizontalLines;
    std::vector<sf::RectangleShape> verticalLines;    
    sf::Color gridColour;
};


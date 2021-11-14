#pragma once

#include <string>
#include <vector>

#include "SFML/Graphics.hpp"

#include "Global.hh"

class Snake
{
public:
    Snake(const unsigned int& cellSpacing, const float& switchTime, const sf::Color& colour, const sf::Vector2f& initialPosition);
    
    void determineDirection();

    void update(float& deltaTime);
    void draw(sf::RenderWindow& window);

private:
    std::vector<sf::RectangleShape> snakeBlobs;

    unsigned int cellSpacing;

    float switchTime;
    float totalTime = 0.0f;

    sf::Vector2f direction = {0.f, 0.f};
};
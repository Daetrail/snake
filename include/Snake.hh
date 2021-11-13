#pragma once

#include <string>
#include <vector>

#include "SFML/Graphics.hpp"

#include "Global.hh"

class Snake
{
public:
    Snake(const unsigned int& cellSpacing, const float& switchTime, const sf::Color& colour, const sf::Vector2f& initialPosition);
    
    void update(float& deltaTime);

    void draw(sf::RenderWindow& window);

private:
    std::vector<sf::RectangleShape> snakeBlobs;
    std::vector<sf::Vector2f> snakePos;

    unsigned int cellSpacing;

    float switchTime;
    float totalTime = 0.0f;

    sf::Vector2f direction;
    bool isMoving = false;
};
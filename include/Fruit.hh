#pragma once

#include <vector>
#include <random>

#include "SFML/Graphics.hpp"

#include "Snake.hh"

class Fruit
{
public:
    Fruit(const sf::Color& colour, Snake& snake);

    void changePos();

    void update();

    void draw(sf::RenderWindow& window);

private:
    sf::CircleShape fruit;

    std::vector<sf::Vector2f> possiblePos;

    sf::Vector2f currentPos;

    Snake* snake = nullptr;

    std::random_device dev;
    std::mt19937 rng;
    std::uniform_int_distribution<std::mt19937::result_type> dist;
};
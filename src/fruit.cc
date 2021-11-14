#include <vector>
#include <random>

#include "SFML/Graphics.hpp"

#include "Fruit.hh"
#include "Global.hh"
#include "Snake.hh"

Fruit::Fruit(const sf::Color& colour, Snake& snake)
: snake(&snake), rng(this->dev()), dist(0, ((G::WINDOW_WIDTH / G::SQUARE_SPACING) * (G::WINDOW_HEIGHT / G::SQUARE_SPACING)) - 1)
{
    float midpointX = G::SQUARE_SPACING / 2.f;
    float midpointY = midpointX;

    for (size_t x = 0; x < G::WINDOW_WIDTH / G::SQUARE_SPACING; ++x)
    {
        for (size_t y = 0; y < G::WINDOW_HEIGHT / G::SQUARE_SPACING; ++y)
        {
            this->possiblePos.push_back(sf::Vector2f(midpointX, midpointY));
            midpointY += G::SQUARE_SPACING;
        }
        midpointX += G::SQUARE_SPACING;
        midpointY = G::SQUARE_SPACING / 2.f;
    }

    this->fruit.setRadius(G::SQUARE_SPACING / 2 - 5);

    this->fruit.setOrigin(this->fruit.getGlobalBounds().width / 2, this->fruit.getGlobalBounds().height / 2);

    this->fruit.setPosition(this->possiblePos[this->dist(this->rng)]);

    this->fruit.setFillColor(colour);
}

void Fruit::changePos()
{
    this->fruit.setPosition(this->possiblePos[this->dist(this->rng)]);
}

void Fruit::update()
{
    if (this->snake->detectFruitCollision(this->fruit.getGlobalBounds()))
        this->changePos();
}

void Fruit::draw(sf::RenderWindow& window)
{
    window.draw(this->fruit);
}
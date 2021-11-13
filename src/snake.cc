#include "SFML/Graphics.hpp"

#include "Global.hh"
#include "Snake.hh"

Snake::Snake(const unsigned int& cellSpacing, const float& switchTime, const sf::Color& colour, const sf::Vector2f& initialPosition)
: cellSpacing(cellSpacing), switchTime(switchTime)
{
    sf::RectangleShape firstBlob(sf::Vector2f(cellSpacing - 10, cellSpacing - 10)); 
    firstBlob.setOrigin(sf::Vector2f(firstBlob.getGlobalBounds().width / 2, firstBlob.getGlobalBounds().height / 2));

    firstBlob.setPosition(initialPosition);
    firstBlob.setFillColor(colour);

    this->snakeBlobs.push_back(firstBlob);
}

void Snake::draw(sf::RenderWindow& window)
{
    for (auto blob : this->snakeBlobs)
        window.draw(blob);
}
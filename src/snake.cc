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


void Snake::determineDirection()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        this->direction = {-1.f, 0.f};
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        this->direction = {1.f, 0.f};
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        this->direction = {0.f, -1.f};
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        this->direction = {0.f, 1.f};
}

void Snake::update(float& deltaTime)
{
    this->determineDirection();

    this->totalTime += deltaTime;

    if (this->totalTime >= this->switchTime)
    {
        this->snakeBlobs[0].move(this->direction * static_cast<float>(this->cellSpacing));
        
        this->totalTime -= this->switchTime;
    }
}

void Snake::draw(sf::RenderWindow& window)
{
    for (auto blob : this->snakeBlobs)
        window.draw(blob);
}
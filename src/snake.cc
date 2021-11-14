#include "SFML/Graphics.hpp"

#include "Global.hh"
#include "Snake.hh"

Snake::Snake(const unsigned int& cellSpacing, const float& switchTime, const sf::Color& colour, const sf::Vector2f& initialPosition)
: cellSpacing(cellSpacing), switchTime(switchTime), colour(colour)
{
    sf::RectangleShape firstBlob(sf::Vector2f(this->cellSpacing - 10, this->cellSpacing - 10)); 
    firstBlob.setOrigin(sf::Vector2f(firstBlob.getGlobalBounds().width / 2, firstBlob.getGlobalBounds().height / 2));

    firstBlob.setPosition(initialPosition);
    firstBlob.setFillColor(this->colour);

    this->snakeBlobs.push_back(firstBlob);
}


void Snake::determineDirection()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        if (this->direction != sf::Vector2f(1.f, 0.f))
            this->direction = {-1.f, 0.f};
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        if (this->direction != sf::Vector2f(-1.f, 0.f))
            this->direction = {1.f, 0.f};
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if (this->direction != sf::Vector2f(0.f, 1.f))
            this->direction = {0.f, -1.f};
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if (this->direction != sf::Vector2f(0.f, -1.f))
            this->direction = {0.f, 1.f};
    }
}

void Snake::addBlob()
{
    sf::RectangleShape blob(sf::Vector2f(this->cellSpacing - 10, this->cellSpacing - 10)); 
    blob.setOrigin(sf::Vector2f(blob.getGlobalBounds().width / 2, blob.getGlobalBounds().height / 2));

    if (this->direction == sf::Vector2f(-1.f, 0.f))
        blob.setPosition(this->snakeBlobs[this->snakeBlobs.size() - 1].getPosition().x + this->cellSpacing, this->snakeBlobs[this->snakeBlobs.size() - 1].getPosition().y);
    else if (this->direction == sf::Vector2f(1.f, 0.f))
        blob.setPosition(this->snakeBlobs[this->snakeBlobs.size() - 1].getPosition().x - this->cellSpacing, this->snakeBlobs[this->snakeBlobs.size() - 1].getPosition().y);
    else if (this->direction == sf::Vector2f(0.f, 1.f))
        blob.setPosition(this->snakeBlobs[this->snakeBlobs.size() - 1].getPosition().x, this->snakeBlobs[this->snakeBlobs.size() - 1].getPosition().y - this->cellSpacing);
    else if (this->direction == sf::Vector2f(0.f, -1.f))
        blob.setPosition(this->snakeBlobs[this->snakeBlobs.size() - 1].getPosition().x, this->snakeBlobs[this->snakeBlobs.size() - 1].getPosition().y + this->cellSpacing);

    blob.setFillColor(this->colour);

    this->snakeBlobs.push_back(blob);
}

void Snake::moveBody()
{
    for (size_t i = this->snakeBlobs.size() - 1; i > 0; --i)
    {
        this->snakeBlobs[i].setPosition(this->snakeBlobs[i - 1].getPosition());
    }
}

void Snake::manuallyAddBlob(sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Space)
            this->addBlob();
    }
}

void Snake::detectBodyCollision()
{
    for (size_t i = 1; i < this->snakeBlobs.size(); ++i)
    {
        if (this->snakeBlobs[0].getGlobalBounds().intersects(this->snakeBlobs[i].getGlobalBounds()))
            std::exit(0);
    }
}

void Snake::update(float& deltaTime)
{
    this->determineDirection();

    this->totalTime += deltaTime;

    this->detectBodyCollision();

    if (this->totalTime >= this->switchTime)
    {
        this->moveBody();
        this->snakeBlobs[0].move(this->direction * static_cast<float>(this->cellSpacing));
        
        this->totalTime -= this->switchTime;
    }
}

void Snake::draw(sf::RenderWindow& window)
{
    for (auto blob : this->snakeBlobs)
        window.draw(blob);
}
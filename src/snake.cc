#include "SFML/Graphics.hpp"

#include "Global.hh"
#include "Snake.hh"
#include <iostream>

Snake::Snake(const unsigned int& cellSpacing, const float& switchTime, const sf::Color& colour, const sf::Vector2f& initialPosition)
: initialPosition(initialPosition), cellSpacing(cellSpacing), switchTime(switchTime), colour(colour)
{
    sf::RectangleShape firstBlob(sf::Vector2f(this->cellSpacing - 10, this->cellSpacing - 10)); 
    firstBlob.setOrigin(sf::Vector2f(firstBlob.getGlobalBounds().width / 2, firstBlob.getGlobalBounds().height / 2));

    firstBlob.setPosition(this->initialPosition);
    firstBlob.setFillColor(this->colour);

    this->snakeBlobs.push_back(firstBlob);
}


void Snake::determineDirection()
{
    if (!this->outOfBounds)
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
}

void Snake::addBlob()
{
    sf::RectangleShape blob(sf::Vector2f(this->cellSpacing - 10, this->cellSpacing - 10)); 
    blob.setOrigin(sf::Vector2f(blob.getGlobalBounds().width / 2, blob.getGlobalBounds().height / 2));

    if (this->direction == sf::Vector2f(-1.f, 0.f))
        blob.setPosition(this->snakeBlobs[0].getPosition().x + this->cellSpacing, this->snakeBlobs[0].getPosition().y);
    else if (this->direction == sf::Vector2f(1.f, 0.f))
        blob.setPosition(this->snakeBlobs[0].getPosition().x - this->cellSpacing, this->snakeBlobs[0].getPosition().y);
    else if (this->direction == sf::Vector2f(0.f, 1.f))
        blob.setPosition(this->snakeBlobs[0].getPosition().x, this->snakeBlobs[0].getPosition().y - this->cellSpacing);
    else if (this->direction == sf::Vector2f(0.f, -1.f))
        blob.setPosition(this->snakeBlobs[0].getPosition().x, this->snakeBlobs[0].getPosition().y + this->cellSpacing);


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
    if (this->direction != sf::Vector2f(0.f, 0.f))
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Space)
                this->addBlob();
        }
    }
}

void Snake::detectBodyCollision()
{
    for (size_t i = 1; i < this->snakeBlobs.size(); ++i)
    {
        if (this->snakeBlobs[0].getGlobalBounds().intersects(this->snakeBlobs[i].getGlobalBounds()))
            this->reset();
    }
}

void Snake::detectBorderCollision()
{
    if (this->snakeBlobs[0].getPosition().x >= G::WINDOW_WIDTH || this->snakeBlobs[0].getPosition().x <= 0 || this->snakeBlobs[0].getPosition().y >= G::WINDOW_HEIGHT || this->snakeBlobs[0].getPosition().y <= 0)
        this->reset();

    // for (size_t i = 0; i < this->snakeBlobs.size(); ++i)
    // {
    //     if (this->snakeBlobs[i].getPosition().x <= 0)
    //     {
    //         this->snakeBlobs[i].move(static_cast<float>(G::WINDOW_WIDTH) + this->cellSpacing, 0.f);
    //         this->outOfBounds = true;
    //     }
    //     else if (this->snakeBlobs[i].getPosition().x >= G::WINDOW_WIDTH)
    //     {
    //         this->snakeBlobs[i].move(static_cast<float>(G::WINDOW_WIDTH) * -1.f - this->cellSpacing, 0.f);
    //         this->outOfBounds = true;
    //     }
    //     else if (this->snakeBlobs[i].getPosition().y <= 0)
    //     {
    //         this->snakeBlobs[i].move(0.f, static_cast<float>(G::WINDOW_HEIGHT) + this->cellSpacing);
    //         this->outOfBounds = true;
    //     }
    //     else if (this->snakeBlobs[i].getPosition().y >= G::WINDOW_HEIGHT)
    //     {
    //         this->snakeBlobs[i].move(0.f, static_cast<float>(G::WINDOW_HEIGHT) * -1 - this->cellSpacing);
    //         this->outOfBounds = true;
    //     }
    //     else
    //         this->outOfBounds = false;
    // }   
}

bool Snake::detectFruitCollision(const sf::FloatRect& fruitBox)
{
    if (this->snakeBlobs[0].getGlobalBounds().intersects(fruitBox))
    {
        this->addBlob();
        return true;
    }
    return false;
}

void Snake::reset()
{
    this->direction = {0.f, 0.f};
    this->snakeBlobs.clear();

    sf::RectangleShape firstBlob(sf::Vector2f(this->cellSpacing - 10, this->cellSpacing - 10)); 
    firstBlob.setOrigin(sf::Vector2f(firstBlob.getGlobalBounds().width / 2, firstBlob.getGlobalBounds().height / 2));

    firstBlob.setPosition(initialPosition);
    firstBlob.setFillColor(this->colour);

    this->snakeBlobs.push_back(firstBlob);
}

void Snake::update(float& deltaTime)
{
    this->determineDirection();

    this->totalTime += deltaTime;

    this->detectBodyCollision();
    this->detectBorderCollision();

    if (this->totalTime >= this->switchTime)
    {
        this->moveBody();
        // this->detectBorderCollision();
        this->snakeBlobs[0].move(this->direction * static_cast<float>(this->cellSpacing));
        
        this->totalTime -= this->switchTime;
    }
}

void Snake::draw(sf::RenderWindow& window)
{
    for (auto blob : this->snakeBlobs)
        window.draw(blob);
}
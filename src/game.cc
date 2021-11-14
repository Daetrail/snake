#include "SFML/Graphics.hpp"

#include "Game.hh"
#include "Snake.hh"
#include "Fruit.hh"

Game::Game(const unsigned int& cellSpacing, const float& switchTime, const sf::Color& colour, const sf::Color& fruitColour, const sf::Vector2f& initialPosition, const unsigned int& WINDOW_WIDTH, const unsigned int& WINDOW_HEIGHT, const sf::Color& gridColour, const bool& grids)
: snake(cellSpacing, switchTime, colour, initialPosition), fruit(fruitColour, this->snake), cellSpacing(cellSpacing), gridColour(gridColour), grids(grids)
{
    if (this->grids)
    {
        for (unsigned int x = 0; x <= WINDOW_WIDTH; x += this->cellSpacing)
        {
            sf::RectangleShape vline(sf::Vector2f(1.f, WINDOW_HEIGHT));
            
            vline.setPosition(sf::Vector2f(x, 0.f));
            vline.setFillColor(this->gridColour);

            this->verticalLines.push_back(vline);
        }

        for (unsigned int y = 0; y <= WINDOW_HEIGHT; y += this->cellSpacing)
        {
            sf::RectangleShape hline(sf::Vector2f(WINDOW_WIDTH, 1.f));

            hline.setPosition(sf::Vector2f(0.f, y));
            hline.setFillColor(this->gridColour);

            this->horizontalLines.push_back(hline);
        }

        this->verticalLines[this->verticalLines.size() - 1].move(-1.f, 0.f);

        this->horizontalLines[this->horizontalLines.size() - 1].move(0.f, -1.f);
    }
}

void Game::eventLoop(sf::Event& event)
{
    this->snake.manuallyAddBlob(event);
}

void Game::update(float& deltaTime)
{
    this->snake.update(deltaTime);
    this->fruit.update();
}

void Game::draw(sf::RenderWindow& window)
{
    if (this->grids)
    {
        for (auto h : this->horizontalLines)
            window.draw(h);
        
        for (auto v : this->verticalLines)
            window.draw(v);
    }

    snake.draw(window);
    fruit.draw(window);
}
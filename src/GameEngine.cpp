#include "GameEngine.hpp"

GameEngine::GameEngine()
{
    this -> initVariables();
    this -> initWindow();
}

GameEngine::~GameEngine()
{
    delete this -> window;
}

bool GameEngine::isRunning() const
{
    return this -> window -> isOpen();
}

void GameEngine::processInput()
{
    while (this -> window -> pollEvent(this -> event))
    {
        if (this -> event.type == sf::Event::Closed)
        {
            this -> window -> close();
        }
    }
}

void GameEngine::update()
{
    this -> processInput();
}

void GameEngine::render()
{
    this -> window -> clear(sf::Color::Black);
    this -> window -> display();
}

void GameEngine::initVariables()
{
    this -> window = nullptr;
}

void GameEngine::initWindow()
{
    this -> window = new sf::RenderWindow(sf::VideoMode(800, 600), "bitman begins", sf::Style::Default);
}
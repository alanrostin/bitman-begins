#include "GameEngine.hpp"

GameEngine::GameEngine()
{
    this -> initVariables();
    this -> initWindow();
    this -> initEnemies();
}

GameEngine::~GameEngine()
{
    delete this -> window;
}

bool GameEngine::isRunning() const
{
    return this -> window -> isOpen();
}

void GameEngine::spawnEnemy()
{
    this -> enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this -> window -> getSize().x - this -> enemy.getSize().x)),
        0.0f
    );

    this -> enemy.setFillColor(sf::Color::Cyan);

    this -> enemies.push_back(this -> enemy);
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

void GameEngine::processMousePosition()
{
    this -> mousePositionWindow = sf::Mouse::getPosition(*this -> window);
    this -> mousePositionView = this -> window -> mapPixelToCoords(this -> mousePositionWindow);
}

void GameEngine::updateEnemies()
{
    // Updating timer for enemy spawning
    if (this -> enemies.size() < this -> maxEnemies)
    {
        if (this -> enemySpawnTimer >= this -> enemySpawnTimerMax)
        {
            // Spawn the enemy and reset the timer
            this -> spawnEnemy();
            this -> enemySpawnTimer = 0.0f;
        }
        else
        {
            this -> enemySpawnTimer += 1.0f;
        }
    }

    // Move enemies
    // for (auto& enemy : this -> enemies)
    // {
    //     enemy.move(0.0f, 5.0f);
    // }
    
    for (int i = 0; i < this -> enemies.size(); i++)
    {
        this -> enemies[i].move(0.0f, 5.0f);

        // Check if clicked upo
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (this -> enemies[i].getGlobalBounds().contains(this -> mousePositionView))
            {
                this -> enemies.erase(this -> enemies.begin() + i);
            }
        }
    }
}

void GameEngine::update()
{
    this -> processInput();

    this -> processMousePosition();

    this -> updateEnemies();
}

void GameEngine::renderEnemies()
{
    // Render all enemies
    for (auto& enemy : this -> enemies)
    {
        this -> window -> draw(enemy);
    }
}

void GameEngine::render()
{
    this -> window -> clear(sf::Color::Black);
    this -> renderEnemies();
    this -> window -> display();
}

void GameEngine::initVariables()
{
    this -> window = nullptr;

    // Game logic
    this -> points = 0;
    this -> enemySpawnTimerMax = 10.0f;
    this -> enemySpawnTimer = this -> enemySpawnTimerMax;
    this -> maxEnemies = 5;
}

void GameEngine::initWindow()
{
    this -> window = new sf::RenderWindow(sf::VideoMode(800, 600), "bitman begins", sf::Style::Default);

    this -> window -> setFramerateLimit(60);
}

void GameEngine::initEnemies()
{
    this -> enemy.setPosition(100.0f, 100.0f);
    this -> enemy.setSize(sf::Vector2f(50.0f, 50.0f));
    this -> enemy.setFillColor(sf::Color::Cyan);
}
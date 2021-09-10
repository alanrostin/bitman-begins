#include "GameEngine.hpp"

GameEngine::GameEngine()
{
    this -> initVariables();
    this -> initWindow();
    this -> initFont();
    this -> initText();
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

bool GameEngine::getEndGame() const
{
    return this -> endGame;
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

void GameEngine::updateText()
{
    std::stringstream ss;

    ss << "Points: " << this -> points << "\n" 
        << "Health: " << this -> health << "\n";

    this -> uiText.setString(ss.str());
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

    // Moving and updating enemies
    // for (auto& enemy : this -> enemies)
    // {
    //     enemy.move(0.0f, 5.0f);
    // }
    
    for (int i = 0; i < this -> enemies.size(); i++)
    {
        bool deleted = false;

        this -> enemies[i].move(0.0f, 5.0f);

        // If enemies is past the bottom of the screen
        if (this -> enemies[i].getPosition().y > this -> window -> getSize().y)
        {
            this -> enemies.erase(this -> enemies.begin() + i);

            this -> health -= 1;
        }
    }

    // Check if clicked upon
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (this -> mouseHeld == false)
        {
            this -> mouseHeld = true;

            bool deleted = false;

            for (int i = 0; i < this -> enemies.size() && deleted == false; i++)
            {
                if (this -> enemies[i].getGlobalBounds().contains(this -> mousePositionView))
                {
                    deleted = true;

                    this -> enemies.erase(this -> enemies.begin() + i);

                    // Add points
                    this -> points += 10;
                }            
            }
        }
    }
    else
    {
        this -> mouseHeld = false;
    }
}

void GameEngine::update()
{
    this -> processInput();

    if (!this -> endGame)
    {
        this -> processMousePosition();

        this -> updateText();

        this -> updateEnemies();
    }

    // End game condition
    if (this -> health <= 0)
    {
        this -> endGame = true;
    }
}

void GameEngine::renderText(sf::RenderTarget& target)
{
    target.draw(this -> uiText);
}

void GameEngine::renderEnemies(sf::RenderTarget& target)
{
    // Render all enemies
    for (auto& enemy : this -> enemies)
    {
        target.draw(enemy);
    }
}

void GameEngine::render()
{
    this -> window -> clear(sf::Color::Black);

    // Render game objects
    this -> renderEnemies(*this -> window);
    this -> renderText(*this -> window);

    this -> window -> display();
}

void GameEngine::initVariables()
{
    this -> window = nullptr;

    // Game logic
    this -> endGame = false;
    this -> points = 0;
    this -> health = 10;
    this -> enemySpawnTimerMax = 10.0f;
    this -> enemySpawnTimer = this -> enemySpawnTimerMax;
    this -> maxEnemies = 10;
    this -> mouseHeld = false;
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

void GameEngine::initFont()
{
    this -> font.loadFromFile("assets/bit_outline.ttf");
}

void GameEngine::initText()
{
    this -> uiText.setFont(this -> font);
    this -> uiText.setCharacterSize(12);
    this -> uiText.setFillColor(sf::Color::White);
    this -> uiText.setString("NONE");
}
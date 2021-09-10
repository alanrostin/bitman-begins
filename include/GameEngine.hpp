#ifndef GameEngine_hpp
#define GameEngine_hpp

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <SFML/Graphics.hpp>

class GameEngine
{
    public:
        GameEngine();
        ~GameEngine();

        // Accessors
        bool isRunning() const;
        bool getEndGame() const;

        // Functions
        void spawnEnemy();

        void processInput();
        void processMousePosition();

        void updateText();
        void updateEnemies();
        void update();

        void renderText(sf::RenderTarget& target);
        void renderEnemies(sf::RenderTarget& target);
        void render();
    
    private:
        // Window, Event
        sf::RenderWindow* window;
        sf::Event event;

        // Mouse position
        sf::Vector2i mousePositionWindow;
        sf::Vector2f mousePositionView;

        // Assets
        sf::Font font;

        // Text
        sf::Text uiText;

        // Game Logic
        bool endGame;
        unsigned points;
        int health;
        float enemySpawnTimer;
        float enemySpawnTimerMax;
        int maxEnemies;
        bool mouseHeld;

        // Game Object
        std::vector<sf::RectangleShape> enemies;
        sf::RectangleShape enemy;

        void initVariables();
        void initWindow();
        void initEnemies();
        void initFont();
        void initText();
};

#endif
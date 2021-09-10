#ifndef GameEngine_hpp
#define GameEngine_hpp

#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>

class GameEngine
{
    public:
        GameEngine();
        ~GameEngine();

        // Accessors
        bool isRunning() const;

        // Functions
        void spawnEnemy();

        void processInput();
        void processMousePosition();

        void updateEnemies();
        void update();

        void renderEnemies();
        void render();
    
    private:
        // Window, Event
        sf::RenderWindow* window;
        sf::Event event;

        // Mouse position
        sf::Vector2i mousePositionWindow;
        sf::Vector2f mousePositionView;

        // Game Logic
        int points;
        float enemySpawnTimer;
        float enemySpawnTimerMax;
        int maxEnemies;

        // Game Object
        std::vector<sf::RectangleShape> enemies;
        sf::RectangleShape enemy;

        void initVariables();
        void initWindow();
        void initEnemies();
};

#endif
#ifndef GameEngine_hpp
#define GameEngine_hpp

#include <SFML/Graphics.hpp>

class GameEngine
{
    public:
        GameEngine();
        ~GameEngine();

        // Accessors
        bool isRunning() const;

        // Functions
        void processInput();
        void update();
        void render();
    
    private:
        sf::RenderWindow* window;
        sf::Event event;

        void initVariables();
        void initWindow();
};

#endif
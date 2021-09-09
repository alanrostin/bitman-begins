#include "GameEngine.hpp"

int main()
{
    // Init srand
    std::srand(static_cast<unsigned>(time(NULL)));

    // Init game engine
    GameEngine gameEngine;

    // Game Loop
    while (gameEngine.isRunning())
    {
        // Process Input
        
        // Update
        gameEngine.update();

        // Render
        gameEngine.render();
    }

    return 0;
}
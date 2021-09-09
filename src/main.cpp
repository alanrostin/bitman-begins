#include "GameEngine.hpp"

int main()
{
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
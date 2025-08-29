#pragma once

#include <vector>
#include "game/GameObject.hpp"

class Game {
    public:
        Game();
        ~Game();
        void run();
    
    private:
        void processInput();
        void update(float deltaTime);
        void render();

        SDL_Window* window;
        SDL_Renderer* renderer;
        std::vector<GameObject*> gameObjects;
        bool isRunning;
        const float FPS = 60.0f;
};
#pragma once

#include <vector>
#include "game/GameObject.hpp"
#include "SDL3_ttf/SDL_ttf.h"

class Game {
    public:
        Game();
        ~Game();
        void run();
    
    private:
        void processInput();
        void update(float deltaTime);
        void render();
        void renderScore(int score, float x, float y);

        const float FPS = 60.0f;

        SDL_Window* window;
        SDL_Renderer* renderer;
        TTF_Font* font;
        std::vector<GameObject*> gameObjects;
        bool isRunning;

        int aScore;
        int bScore;
};
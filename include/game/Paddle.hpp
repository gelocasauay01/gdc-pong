#pragma once
#include "GameObject.hpp"

class Paddle : public GameObject {
    public:
        Paddle(SDL_FRect rect, SDL_Color color, SDL_Scancode up, SDL_Scancode down);
        ~Paddle();
        void handleEvents(SDL_Event& event) override;
        void update(float deltaTime) override;
    
    private:
        float speed;
        float deltaY;
        SDL_Scancode up;
        SDL_Scancode down;
};
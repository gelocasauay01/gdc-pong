#pragma once
#include <SDL3/SDL.h>

class GameObject {
    public:
        GameObject(SDL_FRect rect, SDL_Color color);
        ~GameObject();

        virtual void handleEvents(SDL_Event& event);
        virtual void update(float deltaTime) = 0;
        void render(SDL_Renderer* renderer);
        bool isCollide(const GameObject& other);
        virtual void onCollide(SDL_FRect collideRect);
        SDL_FRect getRect();

    protected:
        SDL_FRect rect;
        SDL_Color color;
};

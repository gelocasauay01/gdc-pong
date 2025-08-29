#pragma once
#include "GameObject.hpp"

class Ball : public GameObject {
    public:
        Ball(SDL_FRect rect, SDL_Color color);
        ~Ball();
        void update(float deltaTime) override;
        void onCollide(SDL_FRect collideRect) override;

    private:
        float deltaX;
        float deltaY;
        float speed;
};
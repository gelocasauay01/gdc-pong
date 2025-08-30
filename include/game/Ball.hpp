#pragma once
#include <vector>
#include <functional>
#include "GameObject.hpp"

class Ball : public GameObject {
    public:
        Ball(SDL_FRect rect, SDL_Color color);
        ~Ball();
        void update(float deltaTime) override;
        void onCollide(SDL_FRect collideRect) override;
        void setCrashLeft(std::function<void()> func);
        void setCrashRight(std::function<void()> func);

    private:
        float deltaX;
        float deltaY;
        float speed;

        std::function<void()> onCrashLeft;
        std::function<void()> onCrashRight;
};
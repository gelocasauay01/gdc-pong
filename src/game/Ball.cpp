#include "../include/game/Ball.hpp"
#include "../include/game/GameObject.hpp"
#include "../include/engine/Settings.hpp"
#include <iostream> 

Ball::Ball(SDL_FRect rect, SDL_Color color) : GameObject(rect, color), speed(300.0f), deltaX(1), deltaY(1) {}

Ball::~Ball() {}

void Ball::update(float deltaTime) {
    rect.x += deltaX * speed * deltaTime;
    rect.y += deltaY * speed * deltaTime;

    if(rect.x <= 0 || rect.x + rect.w >= SCREEN_WIDTH) {
        
        if(rect.x <= 0) onCrashLeft();
        else onCrashRight();

        deltaX = -deltaX;
        rect.x = SCREEN_WIDTH / 2;
        rect.y = SCREEN_HEIGHT / 2;
    } else if(rect.y <= 0 || rect.y + rect.h >= SCREEN_HEIGHT) {
        deltaY = -deltaY;
        rect.y = rect.y <= 0 ? rect.h : SCREEN_HEIGHT - rect.h;
    }
}

void Ball::onCollide(SDL_FRect collideRect) {
    rect.x = deltaX < 0 ? collideRect.x + collideRect.w : collideRect.x - rect.w;
    deltaX = -deltaX;
}

void Ball::setCrashLeft(std::function<void()> func) {
    onCrashLeft = func;
}

void Ball::setCrashRight(std::function<void()> func) {
    onCrashRight = func;
}

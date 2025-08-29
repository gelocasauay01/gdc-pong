#include "../include/game/Paddle.hpp"
#include "../include/engine/Settings.hpp"

Paddle::Paddle(SDL_FRect rect, SDL_Color color, SDL_Scancode up, SDL_Scancode down) : GameObject(rect, color), up(up), down(down), speed(500.0f) {}

Paddle::~Paddle() {}

void Paddle::handleEvents(SDL_Event& event) {
    const bool* keystate = SDL_GetKeyboardState(NULL);
    if (keystate[up]) {
        deltaY = -1;
    } else if (keystate[down]) {
        deltaY = 1;
    } else {
        deltaY = 0;
    }
}

void Paddle::update(float deltaTime) {
    rect.y += deltaY * speed * deltaTime;

    if(rect.y <= 0) {
        rect.y = 0;
    } else if(rect.y + rect.h >= SCREEN_HEIGHT) {
        rect.y = SCREEN_HEIGHT - rect.h;
    }

}
    

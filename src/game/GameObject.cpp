#include "../include/game/GameObject.hpp"
#include <iostream>

GameObject::GameObject(SDL_FRect rect, SDL_Color color) : rect(rect), color(color) {

}

GameObject::~GameObject() {}

void GameObject::handleEvents(SDL_Event& event) {
    // Handle events specific to this game object
}

void GameObject::update(float deltaTime) {
    // Update the game object's state
}

void GameObject::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}

bool GameObject::isCollide(const GameObject& other) {
    return rect.x + rect.w > other.rect.x 
        && rect.x < other.rect.x + other.rect.w 
        && rect.y + rect.h > other.rect.y
        && rect.y < other.rect.y + other.rect.h;
}

void GameObject::onCollide(SDL_FRect collideRect) {
    
}

SDL_FRect GameObject::getRect(){
    return rect;
}

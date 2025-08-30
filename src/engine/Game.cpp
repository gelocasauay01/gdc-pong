#include "../include/engine/Settings.hpp"
#include "../include/engine/Game.hpp"
#include "../include/game/GameObject.hpp"
#include "../include/game/Ball.hpp"
#include "../include/game/Paddle.hpp"
#include <string>

Game::Game() {
    // Initialize game objects
    if (!SDL_Init(SDL_INIT_VIDEO) || !TTF_Init()) {
        SDL_Log("SDL_Init Error: %s", SDL_GetError());
        return;
    }

    window = SDL_CreateWindow("Pong", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
    if (!window) {
        SDL_Log("SDL_CreateWindow Error: %s", SDL_GetError());
        SDL_Quit();
        return;
    }

    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    font = TTF_OpenFont("C:/Windows/Fonts/Arial.ttf", 24);
    
    aScore = 0;
    bScore = 0;

    Ball* ball = new Ball({SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 10, 10}, {255, 255, 255, 255});
    ball->setCrashLeft([this]() { bScore++; });
    ball->setCrashRight([this]() { aScore++; });

    gameObjects.push_back(ball);
    gameObjects.push_back(new Paddle({25, SCREEN_HEIGHT / 2, 10, 50}, {255, 255, 255, 255}, SDL_SCANCODE_W, SDL_SCANCODE_S));
    gameObjects.push_back(new Paddle({SCREEN_WIDTH - 25, SCREEN_HEIGHT / 2, 10, 50}, {255, 255, 255, 255}, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN));

    isRunning = true;
}

Game::~Game() {
    // Clean up resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::run() {
    // Main game loop
    float currentTime = 0.0f;
    float lastTimeSinceFrame = 0.0f;

    while (isRunning && aScore < 7 && bScore < 7) {
        currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTimeSinceFrame) / 1000.0f;
        lastTimeSinceFrame = currentTime;

        processInput();
        update(deltaTime);
        render();
    }
}

void Game::processInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            isRunning = false;
        } else {
            for (auto& gameObject : gameObjects) {
                gameObject->handleEvents(event);
            }
        }
    }

    for(GameObject* a : gameObjects) {
        for(GameObject* b: gameObjects) {
            if(a != b && a->isCollide(*b)) {
                a->onCollide(b->getRect());
                b->onCollide(a->getRect());
            }
        }
    }
}

void Game::update(float deltaTime) {
    for (GameObject* gameObject : gameObjects) {
        gameObject->update(deltaTime);
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw line in the middle
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_FRect lineRect = {SCREEN_WIDTH / 2, 0, 10, SCREEN_HEIGHT};
    SDL_RenderFillRect(renderer, &lineRect);

    for (GameObject* gameObject : gameObjects) {
        gameObject->render(renderer);
    }

    renderScore(aScore, SCREEN_WIDTH / 4.0f, 10);
    renderScore(bScore, 3.0f / 4.0f * SCREEN_WIDTH, 10);
    SDL_RenderPresent(renderer);
}

void Game::renderScore(int score, float x, float y) {
    std::string scoreText = std::to_string(score).c_str();
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), 0, {255,255,255,255});
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_DestroySurface(textSurface);

    SDL_FRect dst = {x, y, (float)scoreText.size() * 24, 24};
    SDL_RenderTexture(renderer, texture, NULL, &dst);
    SDL_DestroyTexture(texture);
}
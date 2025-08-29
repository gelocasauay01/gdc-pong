#include "../include/engine/Settings.hpp"
#include "../include/engine/Game.hpp"
#include "../include/game/GameObject.hpp"
#include "../include/game/Ball.hpp"
#include "../include/game/Paddle.hpp"

Game::Game() {
    // Initialize game objects
    if (!SDL_Init(SDL_INIT_VIDEO)) {
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

    gameObjects.push_back(new Ball({SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 10, 10}, {255, 255, 255, 255}));
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

    while (isRunning) {
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
    for (GameObject* gameObject : gameObjects) {
        gameObject->render(renderer);
    }
    SDL_RenderPresent(renderer);
}

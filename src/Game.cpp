#include "Game.h"
#include "Logger.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <iostream>
#include <string>

Game::Game() {
    Logger::Log("Game object created.");
    isRunning = false;
}

Game::~Game() {
}

glm::vec2 playerPosition;
glm::vec2 playerVelocity;

void Game::Setup() {
    playerPosition = glm::vec2(-192.0, (600.0/2)-(192.0/2.0));
    // Movement is in pixels per second
    playerVelocity = glm::vec2(100.0, 0.0);
}

void Game::Initialize() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        Logger::Error("Error initializing SDL.");
        return;
    }
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    windowWidth = 1024; //displayMode.w;
    windowHeight = 600; //displayMode.h;
    window = SDL_CreateWindow(
        "2D Game Engine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_BORDERLESS
    );
    if (!window) {
        Logger::Error("Error creating SDL window.");
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        Logger::Error("Error creating SDL renderer.");
    }
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    cycle = 0;
    isRunning = true;
}

void Game::Run() {
    Setup();
    while (isRunning) {
        ProcessInput();
        Update();
        Render();
    }
    std::cout << "cycles run: " << cycle << std::endl;
    Logger::Log("Cycles run: " + cycle);
}

void Game::ProcessInput() {
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        switch (sdlEvent.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
                    isRunning = false;
                }
                break;
        }
    }
}

void Game::Update() {
    // Lock frame until frame rate is ready.
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPrevFrame);
    if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME) {
        SDL_Delay(timeToWait);
    }

    // Diff of ticks since last frame, converted to seconds
    double deltaTime = (SDL_GetTicks() - millisecsPrevFrame) / 1000.0;

    // Store "previous" frame time
    millisecsPrevFrame = SDL_GetTicks();

    playerPosition.x += playerVelocity.x * deltaTime;
    playerPosition.y += playerVelocity.y * deltaTime;

    if (playerPosition.x > 1024) {
        playerPosition.x = -192.0;
        cycle++;
    }
}

void Game::Render() {
    if (cycle % 2) {
        SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255); // Cornflower blue
    } else {
        SDL_SetRenderDrawColor(renderer, 100, 92.9, 73.2, 255); // Wall color
    }
    SDL_RenderClear(renderer);

    // Load PNG texture
    SDL_Surface* surface = IMG_Load("./assets/images/skateboard_x4.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_Rect destRect = {
        static_cast<int>(playerPosition.x),
        static_cast<int>(playerPosition.y),
        192,
        192
    };
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
    SDL_DestroyTexture(texture);

    SDL_RenderPresent(renderer);
}

void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

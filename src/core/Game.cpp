/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#include "Game.hpp"
#include "raylib.h"

Game::Game(int screenHeight, int screenWidth) {
    InitWindow(screenWidth, screenHeight,
               "raylib [core] example - basic window");
    SetTargetFPS(60);
    SetTraceLogLevel(LOG_NONE);
}

Game::~Game() {
    CloseWindow();
}

void Game::run() {
    while (!WindowShouldClose()) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsedTime = currentTime - _lastTime;
        _deltaTime = elapsedTime.count();
        _lastTime = currentTime;

        update(_deltaTime);
        draw();
    }
}

void Game::update(float deltaTime) {
    (void)deltaTime;
}

void Game::draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    EndDrawing();
}
/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#include "Game.hpp"
#include "raylib.h"

Game::Game(int screenWidth, int screenHeight)
    : _screenWidth(screenWidth), _screenHeight(screenHeight) {
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

void drawGrid(int screenWidth, int screenHeight) {
    const int gridSpacing = 50;
    const Color gridColor = LIGHTGRAY;

    for (int x = 0; x < screenWidth; x += gridSpacing) {
        DrawLine(x, 0, x, screenHeight, gridColor);
    }

    for (int y = 0; y < screenHeight; y += gridSpacing) {
        DrawLine(0, y, screenWidth, y, gridColor);
    }
}

void Game::draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    drawGrid(_screenWidth, _screenHeight);

    EndDrawing();
}

/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#include "Game.hpp"
#include "raylib.h"
#include "raymath.h"

Game::Game(int screenWidth, int screenHeight)
    : _screenWidth(screenWidth), _screenHeight(screenHeight) {
    InitWindow(screenWidth, screenHeight, "Brad Pitt Simulator");
    SetTargetFPS(60);
    // SetTraceLogLevel(LOG_NONE);

    _lastTime = std::chrono::high_resolution_clock::now();

    _player = std::make_unique<Player>();
    _world = std::make_unique<World>();
    _hud = std::make_unique<HUD>();

    initCamera();
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
    Vector2 direction = {0, 0};
    float speed = 500 * deltaTime;

    direction.x = IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT);
    direction.y = IsKeyDown(KEY_DOWN) - IsKeyDown(KEY_UP);

    if (Vector2Length(direction) > 0) {
        direction = Vector2Normalize(direction);
        direction = Vector2Scale(direction, speed);

        _player->move(direction);
        _player->update(deltaTime);
        // Move the player on the X axis
        Vector2 newPosition = _player->getPosition();
        newPosition.x += direction.x;
        _player->setPosition(newPosition);

        // Check for collisions on the X axis
        Rectangle playerBoundingBox = _player->getBoundingBox();
        Rectangle collision = _world->getCollisions(playerBoundingBox);

        // If a collision is detected, adjust the player's position on the X
        // axis
        if (collision.width != 0 && collision.height != 0) {
            newPosition.x -= direction.x;
            _player->setPosition(newPosition);
        }

        // Move the player on the Y axis
        newPosition = _player->getPosition();
        newPosition.y += direction.y;
        _player->setPosition(newPosition);

        // Check for collisions on the Y axis
        playerBoundingBox = _player->getBoundingBox();
        collision = _world->getCollisions(playerBoundingBox);

        // If a collision is detected, adjust the player's position on the Y
        // axis
        if (collision.width != 0 && collision.height != 0) {
            newPosition.y -= direction.y;
            _player->setPosition(newPosition);
        }
    }
    _hud->update(deltaTime, 1, 0); // changer valeurs pour celles du joueur
    followPlayer();

    (void)deltaTime;
}

void drawGrid(int screenWidth, int screenHeight, Camera2D camera) {
    const int gridSpacing = 32;
    const Color gridColor = LIGHTGRAY;

    Vector2 cameraTarget = camera.target;

    for (float x = camera.target.x - (int)camera.target.x % gridSpacing -
                   screenWidth / 2;
         x < camera.target.x + screenWidth / 2; x += gridSpacing) {
        DrawLine(x, camera.target.y - screenHeight / 2, x,
                 camera.target.y + screenHeight / 2, gridColor);
    }

    for (float y = camera.target.y - (int)camera.target.y % gridSpacing -
                   screenHeight / 2;
         y < camera.target.y + screenHeight / 2; y += gridSpacing) {
        DrawLine(camera.target.x - screenWidth / 2, y - 5,
                 camera.target.x + screenWidth / 2, y - 5, gridColor);
    }

    float horizontalOffset = 500;
    float verticalOffset = 225;

    DrawLine(cameraTarget.x - horizontalOffset, cameraTarget.y - verticalOffset,
             cameraTarget.x + horizontalOffset, cameraTarget.y - verticalOffset,
             RED);
    DrawLine(cameraTarget.x + horizontalOffset, cameraTarget.y - verticalOffset,
             cameraTarget.x + horizontalOffset, cameraTarget.y + verticalOffset,
             RED);
    DrawLine(cameraTarget.x + horizontalOffset, cameraTarget.y + verticalOffset,
             cameraTarget.x - horizontalOffset, cameraTarget.y + verticalOffset,
             RED);
    DrawLine(cameraTarget.x - horizontalOffset, cameraTarget.y + verticalOffset,
             cameraTarget.x - horizontalOffset, cameraTarget.y - verticalOffset,
             RED);
}

void Game::draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode2D(_camera);

    drawGrid(_screenWidth, _screenHeight, _camera);
    _world->drawChunk({0, 0});

    _player->draw();

    EndMode2D();

    _hud->draw();
    EndDrawing();
}

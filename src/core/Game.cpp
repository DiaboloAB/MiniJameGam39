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
    _car = std::make_unique<Car>();
    _world = std::make_unique<World>();
    _hud = std::make_unique<HUD>();
    _entityManager = std::make_unique<EntityManager>();
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

    if (!_drivingMode) {
        handlePlayerInput(deltaTime, direction, speed);
    }

    if (_drivingMode) {
        handleCarInput(deltaTime);
    }

    _hud->update(deltaTime, _player->getPanic(), _player->getBonus());
    followPlayer();

    _spawnTimer += deltaTime;
    if (_spawnTimer > 3) {
        _entityManager->spawnEntity(_player->getPosition());
        _spawnTimer = 0;
    }
    _entityManager->update(deltaTime, _player.get(), _world.get());
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
}

void drawCameraTarget(Camera2D camera) {
    Vector2 cameraTarget = camera.target;

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
    _world->drawChunks(_camera.target - _camera.offset,
                       (Vector2){(float)_screenWidth, (float)_screenHeight});
    _world->drawChunks(_camera.target - _camera.offset + (Vector2){200, 200},
                       (Vector2){(float)_screenWidth, (float)_screenHeight} -
                           (Vector2){400, 400});

    if (_drivingMode && _car) {
        _car->draw();
    } else {
        _player->draw();
        if (_car) {
            _car->draw();
        }
    }
    _entityManager->draw();

    // drawCameraTarget(_camera);

    EndMode2D();

    _hud->draw();
    EndDrawing();
}

void Game::handlePlayerInput(float deltaTime, Vector2 direction, float speed) {
    if (Vector2Length(direction) > 0) {
        direction = Vector2Normalize(direction);
        direction = Vector2Scale(direction, speed);

        _player->move(direction);
        _player->update(deltaTime);
        Vector2 newPosition = _player->getPosition();
        newPosition.x += direction.x;
        _player->setPosition(newPosition);

        Rectangle playerBoundingBox = _player->getBoundingBox();
        Rectangle collision = _world->getCollisions(playerBoundingBox);

        if (collision.width != 0 && collision.height != 0) {
            newPosition.x -= direction.x;
            _player->setPosition(newPosition);
        }

        newPosition = _player->getPosition();
        newPosition.y += direction.y;
        _player->setPosition(newPosition);

        playerBoundingBox = _player->getBoundingBox();
        collision = _world->getCollisions(playerBoundingBox);

        if (collision.width != 0 && collision.height != 0) {
            newPosition.y -= direction.y;
            _player->setPosition(newPosition);
        }
    }
    if (_car && CheckCollisionRecs(_player->getBoundingBox(), _car->getBoundingBox())) {
        _drivingMode = true;
        _drivingTimer = 10.0f;
        _car->setPosition(_player->getPosition());
    }
}

void Game::handleCarInput(float deltaTime) {
    _drivingTimer -= deltaTime;

    if (_car) {
        if (IsKeyDown(KEY_UP)) {
            _car->accelerate(600 * deltaTime);  // Accélère
        }
        if (IsKeyDown(KEY_DOWN)) {
            _car->accelerate(-150 * deltaTime); // Freine
        }
        if (IsKeyDown(KEY_LEFT)) {
            _car->turn(-120 * deltaTime); // Tourne à gauche
        }
        if (IsKeyDown(KEY_RIGHT)) {
            _car->turn(120 * deltaTime); // Tourne à droite
        }
        Vector2 prevPosition = _car->getPosition();
        _car->update(deltaTime);
        Vector2 newPosition = _car->getPosition();
        Rectangle carBoundingBox = _car->getBoundingBox();
        Rectangle collision = _world->getCollisions(carBoundingBox);
        if (collision.width != 0 && collision.height != 0) {
            _car->setPosition({newPosition.x, prevPosition.y});
            if (_world->getCollisions(_car->getBoundingBox()).width != 0) {
                _car->setPosition(prevPosition);
            }
            _car->setPosition({prevPosition.x, newPosition.y});
            if (_world->getCollisions(_car->getBoundingBox()).width != 0) {
                _car->setPosition(prevPosition);
            }
        }
        Vector2 newPositionP = _car->getPosition();
        _player->setPosition(newPositionP);
    }
    if (_drivingTimer <= 0) {
        _drivingMode = false;
        if (_car) {
            _player->setPosition(_car->getPosition());
        }
        _car.reset();
    }
}
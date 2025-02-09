/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#include "./scene/SceneType.hpp"
#include "Game.hpp"
#include "core/AudioManager.hpp"
#include "raylib.h"
#include "raymath.h"

Game::Game(int screenWidth, int screenHeight)
    : _screenWidth(screenWidth), _screenHeight(screenHeight) {
    // SetTraceLogLevel(LOG_NONE);

    _lastTime = std::chrono::high_resolution_clock::now();

    _player = std::make_unique<Player>();
    _car = std::make_unique<Car>();
    _world = std::make_unique<World>();
    _hud = std::make_unique<HUD>();
    _entityManager = std::make_unique<EntityManager>();
    _gameManager = std::make_unique<GameManager>(
        _world.get(), _entityManager.get(), _player.get());
    initCamera();

    // get a value on a circle of radius 1000
    // _winPosition = {1500 * cos(PI / 4), 1500 * sin(PI / 4)};
    _winPosition = _world->getRandomWinPoint();

    Image arrow = LoadImage("assets/arrow.png");
    _arrow = LoadTextureFromImage(arrow);
    Image drop = LoadImage("assets/drop.png");
    _drop = LoadTextureFromImage(drop);

    _heartBeatShader = LoadShader(0, "assets/shaders/heart_beat.fs");
    _resolutionLoc = GetShaderLocation(_heartBeatShader, "resolution");
    _timeLoc = GetShaderLocation(_heartBeatShader, "time");
    _healthLoc = GetShaderLocation(_heartBeatShader, "health");

    Image plane = LoadImage("assets/plane.png");
    _plane = LoadTextureFromImage(plane);
    _planeScale = (float)_screenWidth / _plane.width;
    _planePosition = {-screenWidth, 0};
}

Game::~Game() {
}

SceneType Game::update(float deltaTime) {
    Vector2 direction = {0, 0};
    float speed = _player->getSpeed() * deltaTime;

    direction.x = IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT);
    direction.y = IsKeyDown(KEY_DOWN) - IsKeyDown(KEY_UP);

    if (!_player->_drivingMode) {
        handlePlayerInput(deltaTime, direction, speed);
    } else {
        handleCarInput(deltaTime);
    }

    if (!_playerSaved) {
        _hud->update(deltaTime, _player->getPanic(), _player->getBonus());
    }
    followPlayer();

    _gameManager->update(deltaTime);

    if (CheckCollisionCircles(_player->getPosition(), 20, _winPosition, 50)) {
        _planeMoving = true;
    }
    if (_planeMoving) {
        _planePosition.x += _planeSpeed * deltaTime;

        float planeLeft = _planePosition.x;
        float planeRight = _planePosition.x + _screenWidth;
        float playerX = _player->getPosition().x;

        if (!_playerSaved && playerX >= planeLeft && playerX <= planeRight) {
            _playerSaved = true;
        }

        if (_playerSaved && _planePosition.x > _screenWidth) {
            _planeMoving = false;
            GameStats::finalTime = _hud->getElapsedTime();
            GameStats::finalBonus = _player->getBonus();
            // resetGame();
            return SceneType::VICTORY;
        }
    }
    return SceneType::GAME;
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
    BeginMode2D(_camera);

    drawGrid(_screenWidth, _screenHeight, _camera);
    _world->drawChunks(_camera.target - _camera.offset,
                       (Vector2){(float)_screenWidth, (float)_screenHeight});

    if (!_playerSaved) {
        if (_player->_drivingMode)
            _car->draw();
        else
            _player->draw();
    }
    drawDrop();
    _entityManager->draw();

    _world->drawChunks(_camera.target - _camera.offset,
                       (Vector2){(float)_screenWidth, (float)_screenHeight}, 2);

    // drawCameraTarget(_camera);
    if (!_playerSaved) {
        drawArrow();
    }
    drawArrow();
    _gameManager->draw();

    EndMode2D();

    // BeginShaderMode(_heartBeatShader);
    // DrawRectangle(0, 0, _screenWidth, _screenHeight, BLACK);
    // EndShaderMode();
    if (_player->_drivingMode) {
        _hud->drawTimer(_player->_drivingTimer);
    }
    if (_player->_panic > 3) {
        float resolution[2] = {(float)_screenWidth, (float)_screenHeight};
        SetShaderValue(_heartBeatShader, _resolutionLoc, resolution,
                       SHADER_UNIFORM_VEC2);
        float time = GetTime();
        SetShaderValue(_heartBeatShader, _timeLoc, &time, SHADER_UNIFORM_FLOAT);
        float health = (16 - _player->_panic) / 16;
        SetShaderValue(_heartBeatShader, _healthLoc, &health,
                       SHADER_UNIFORM_FLOAT);

        BeginShaderMode(_heartBeatShader);
        DrawRectangle(0, 0, _screenWidth, _screenHeight, BLACK);
        EndShaderMode();
    }
    _hud->draw();
    if (_planeMoving) {
        DrawTextureEx(_plane, _planePosition, 0.0f, _planeScale, WHITE);
    }
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
    _car->setPosition(_player->getPosition());
}

void Game::handleCarInput(float deltaTime) {
    _player->_drivingTimer -= deltaTime;

    if (_car) {
        if (IsKeyDown(KEY_UP)) {
            _car->accelerate(600 * deltaTime);
        }
        if (IsKeyDown(KEY_DOWN)) {
            _car->accelerate(-150 * deltaTime);
        }
        if (IsKeyDown(KEY_LEFT)) {
            _car->turn(-120 * deltaTime);
        }
        if (IsKeyDown(KEY_RIGHT)) {
            _car->turn(120 * deltaTime);
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
    if (_player->_drivingTimer <= 0) {
        AudioManager::getInstance().stopCar();
        _player->_drivingMode = false;
        _player->setPosition(_car->getPosition());
    }
}

void Game::drawArrow() {
    float angle = atan2(_winPosition.y - _player->getPosition().y,
                        _winPosition.x - _player->getPosition().x);

    Vector2 direction = {cos(angle), sin(angle)};
    float distance =
        Vector2Length(Vector2Subtract(_winPosition, _player->getPosition()));
    distance /= 2;
    distance = distance > 200 ? 200 : distance;

    Vector2 coss = {cos(GetTime() * 4) * 30, cos(GetTime() * 4) * 30};
    Vector2 dirCos = Vector2Multiply(direction, coss);

    direction = Vector2Scale(direction, distance);
    direction = Vector2Add(direction, dirCos);

    DrawTexturePro(
        _arrow, (Rectangle){0, 0, (float)_arrow.width, (float)_arrow.height},
        (Rectangle){_player->getPosition().x + direction.x,
                    _player->getPosition().y + direction.y, 100, 100},
        (Vector2){50, 50}, angle * RAD2DEG, WHITE);
}

void Game::drawDrop() {
    DrawTexturePro(_drop,
                   (Rectangle){0, 0, (float)_drop.width, (float)_drop.height},
                   (Rectangle){_winPosition.x, _winPosition.y, 100, 100},
                   (Vector2){50, 50}, 0, WHITE);
}

void Game::resetGame() {
    // _player->setPosition({0, 0});
    // _player->_drivingMode = false;
    // _player->_drivingTimer = 0.0f;
    // _car.reset();
    // _hud->reset();
}
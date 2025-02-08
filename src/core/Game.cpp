/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#include "./scene/Scene.hpp"
#include "Game.hpp"
#include "raylib.h"
#include "raymath.h"

Game::Game(int screenWidth, int screenHeight)
    : _screenWidth(screenWidth), _screenHeight(screenHeight) {
    // SetTraceLogLevel(LOG_NONE);

    _lastTime = std::chrono::high_resolution_clock::now();

    _player = std::make_unique<Player>();
    _world = std::make_unique<World>();
    _hud = std::make_unique<HUD>();
    _entityManager = std::make_unique<EntityManager>();
    initCamera();

    // get a value on a circle of radius 1000
    // _winPosition = {1500 * cos(PI / 4), 1500 * sin(PI / 4)};
    _winPosition = {1000, 0};

    Image arrow = LoadImage("assets/arrow.png");
    _arrow = LoadTextureFromImage(arrow);
    Image drop = LoadImage("assets/drop.png");
    _drop = LoadTextureFromImage(drop);

    Image imagePlane = LoadImage("assets/plane.png");
    _plane = LoadTextureFromImage(imagePlane);
}

Game::~Game() {
}

SceneType Game::run() {
    while (!WindowShouldClose()) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsedTime = currentTime - _lastTime;
        _deltaTime = elapsedTime.count();
        _lastTime = currentTime;

        update(_deltaTime);
        draw();
    }
    return SceneType::GAME;
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
    _hud->update(deltaTime, _player->getPanic(), _player->getBonus());
    followPlayer();
    _spawnTimer += deltaTime;
    if (_spawnTimer > 3) {
        _entityManager->spawnEntity(_player->getPosition());
        _spawnTimer = 0;
    }
    _plane_x += 2.8;
    _plane_y += -2;

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

    drawDrop();
    _entityManager->draw();
    _player->draw();

    // drawCameraTarget(_camera);
    drawArrow();

    EndMode2D();
    isOnDrop();
    _hud->draw();
    EndDrawing();
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



void updatePlane(float deltaTime, int frames)
{
}
void Game::isOnDrop()
{

    float distance = Vector2Length(Vector2Subtract(_winPosition, _player->getPosition()));
    Vector2 direction = {cos(45), sin(45)};
    Vector2 playerPosition = _player->getPosition();
    std::cout << "OKEYYYYYYYYYYYYYYYY" << std::endl;


    if (distance < 30) {
            DrawTexturePro(_plane, (Rectangle){0, 0, _plane.width, _plane.height},
            (Rectangle){_plane_x - 600, _plane_y + 1400, 800, 800},
            (Vector2){0, 0}, 65, WHITE);
            _inDrop = true;
    } else {
        _inDrop = false;
    }
    if (_inDrop == true && (_plane_x + 100 > playerPosition.x && _plane_x - 100 < playerPosition.x) && (_plane_y + 100 > playerPosition.y && _plane_y - 100 < playerPosition.y)) {
        _player->setPosition((Vector2){_plane_x + 80, _plane_y + 80});
    }
}

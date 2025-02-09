/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#ifndef GAME_H
#define GAME_H

#include "HUD.hpp"
#include "core/GameManager.hpp"
#include "groupies/EntityManager.hpp"
#include "player/Car.hpp"
#include "player/Player.hpp"
#include "world/World.hpp"

// std
#include <chrono>
#include <memory>

#include "scene/SceneType.hpp"
class Game {
public:
    Game(int screenWidth = 1920, int screenHeight = 1080);
    ~Game();

    void initCamera();
    void followPlayer();

    SceneType update(float deltaTime);
    void draw();
    void drawArrow();
    void drawDrop();

    void handlePlayerInput(float deltaTime, Vector2 direction, float speed);
    void handleCarInput(float deltaTime);
    void resetGame();

private:
    float _deltaTime;
    std::chrono::high_resolution_clock::time_point _lastTime;

    int _screenWidth;
    int _screenHeight;

    Camera2D _camera;

    std::unique_ptr<Player> _player;
    std::unique_ptr<Car> _car;

    std::unique_ptr<World> _world;
    std::unique_ptr<GameManager> _gameManager;
    std::unique_ptr<EntityManager> _entityManager;

    std::unique_ptr<HUD> _hud;
    Texture2D _arrow;
    Texture2D _drop;

    float _spawnTimer;
    bool _drivingMode = false;
    float _drivingTimer = 0.0f;

    Vector2 _winPosition;

    Shader _heartBeatShader;
    int _resolutionLoc;
    int _timeLoc;
    int _healthLoc;

    Texture2D _plane;
    Vector2 _planePosition;
    bool _planeMoving = false;
    float _planeSpeed = 1200.0f;
    float _planeScale = 1.0f;
};

#endif  // GAME_H
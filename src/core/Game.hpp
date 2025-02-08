/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#ifndef GAME_H
#define GAME_H

#include "HUD.hpp"
#include "groupies/EntityManager.hpp"
#include "player/Player.hpp"
#include "world/World.hpp"

// std
#include <chrono>
#include <memory>

enum class SceneType;

class Game {
public:
    Game(int screenWidth = 1920, int screenHeight = 1080);
    ~Game();

    void initCamera();
    void followPlayer();

    SceneType run();
    void update(float deltaTime);
    void draw();
    void drawArrow();
    void drawDrop();
    void isOnDrop();

private:
    float _deltaTime;
    std::chrono::high_resolution_clock::time_point _lastTime;

    int _screenWidth;
    int _screenHeight;

    Camera2D _camera;

    std::unique_ptr<Player> _player;

    std::unique_ptr<World> _world;

    std::unique_ptr<HUD> _hud;
    std::unique_ptr<EntityManager> _entityManager;
    Texture2D _arrow;
    Texture2D _drop;

    float _spawnTimer;

    Vector2 _winPosition;

    Texture2D _plane;
    float _plane_x = 0.0f;
    float _plane_y = 0.0f;
    bool _inDrop = false;
};

#endif  // GAME_H
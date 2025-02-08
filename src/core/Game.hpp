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
};

#endif  // GAME_H
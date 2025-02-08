/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#ifndef GAME_H
#define GAME_H

#include "groupies/EntityManager.hpp"
#include "player/Player.hpp"
#include "world/World.hpp"
#include "player/Car.hpp"
#include "HUD.hpp"

// std
#include <chrono>
#include <memory>

class Game {
public:
    Game(int screenWidth = 800, int screenHeight = 450);
    ~Game();

    void initCamera();
    void followPlayer();

    void run();
    void update(float deltaTime);
    void draw();

private:
    float _deltaTime;
    std::chrono::high_resolution_clock::time_point _lastTime;

    int _screenWidth;
    int _screenHeight;

    Camera2D _camera;

    std::unique_ptr<Player> _player;
    std::unique_ptr<Car> _car;

    std::unique_ptr<World> _world;

    std::unique_ptr<HUD> _hud;
    std::unique_ptr<EntityManager> _entityManager;

    float _spawnTimer;
};

#endif  // GAME_H
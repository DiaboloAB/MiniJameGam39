#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <iostream>
#include <memory>

#include "../core/Game.hpp"
#include "SceneType.hpp"
#include "gameover/GameOver.hpp"
#include "menu/Menu.hpp"
#include "raylib.h"
#include "victory/Victory.hpp"

class SceneManager {
public:
    SceneManager(int screenWidth, int screenHeight);

    ~SceneManager() {
        CloseAudioDevice();
        CloseWindow();
    }

    void run();

private:
    int _screenWidth;
    int _screenHeight;
    SceneType _currentScene;
    Music _music;
    std::unique_ptr<Menu> _menu;
    std::unique_ptr<Game> _game;
    std::unique_ptr<GameOver> _gameOver;
    std::unique_ptr<Victory> _victory;

    float _deltaTime;
    std::chrono::high_resolution_clock::time_point _lastTime;

    void update();
    void draw();
};

#endif /* !SCENE_HPP_ */

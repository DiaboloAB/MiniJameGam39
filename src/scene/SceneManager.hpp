#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <iostream>
#include <memory>

#include "../core/Game.hpp"
#include "SceneType.hpp"
#include "menu/Menu.hpp"
#include "raylib.h"

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

    std::unique_ptr<Menu> _menu;
    std::unique_ptr<Game> _game;

    float _deltaTime;
    std::chrono::high_resolution_clock::time_point _lastTime;

    void update();
    void draw();
};

#endif /* !SCENE_HPP_ */

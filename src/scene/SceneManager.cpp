/*
** EPITECH PROJECT, 2025
** MiniJameGam39
** File description:
** Scene
*/

#include "../menu/Menu.hpp"
#include "SceneManager.hpp"

SceneManager::SceneManager(int screenWidth, int screenHeight)
    : _screenWidth(screenWidth),
      _screenHeight(screenHeight),
      _currentScene(SceneType::MENU) {
    _lastTime = std::chrono::high_resolution_clock::now();
    _deltaTime = 0;
    InitAudioDevice();
    // set sound to 50% volume
    // SetMasterVolume(0.05);
    SetMasterVolume(0.0);
    InitWindow(screenWidth, screenHeight, "Brad Pitt Simulator");
    SetTargetFPS(60);

    _menu = std::make_unique<Menu>(screenWidth, screenHeight);
    _game = std::make_unique<Game>(screenWidth, screenHeight);
}

void SceneManager::run() {
    while (!WindowShouldClose() && _currentScene != SceneType::EXIT) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsedTime = currentTime - _lastTime;
        _deltaTime = elapsedTime.count();
        _lastTime = currentTime;

        update();
        draw();
    }
}

void SceneManager::update() {
    switch (_currentScene) {
        case SceneType::MENU:
            _currentScene = _menu->update(_deltaTime);
            break;
        case SceneType::GAME:
            _currentScene = _game->update(_deltaTime);
            break;
        case SceneType::EXIT:
            return;
    }
}

void SceneManager::draw() {
    BeginDrawing();
    ClearBackground(GetColor(0x052c46ff));
    switch (_currentScene) {
        case SceneType::MENU:
            _menu->draw();
            break;
        case SceneType::GAME:
            _game->draw();
            break;
        case SceneType::EXIT:
            return;
    }
    EndDrawing();
}
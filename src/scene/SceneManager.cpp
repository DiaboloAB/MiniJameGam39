/*
** EPITECH PROJECT, 2025
** MiniJameGam39
** File description:
** Scene
*/

#include "../menu/Menu.hpp"
#include "SceneManager.hpp"
#include "core/AudioManager.hpp"

SceneManager::SceneManager(int screenWidth, int screenHeight)
    : _screenWidth(screenWidth),
      _screenHeight(screenHeight),
      _currentScene(SceneType::MENU){
    _lastTime = std::chrono::high_resolution_clock::now();
    _deltaTime = 0;
    // SetMasterVolume(0.5);
    // SetMasterVolume(0.0);
    InitWindow(screenWidth, screenHeight, "Brad Pitt Simulator");
    SetTargetFPS(60);
    InitAudioDevice();
    AudioManager::getInstance().init();
    _music = LoadMusicStream("assets/audio/music.ogg");
    SetMusicVolume(_music, 0.5);
    PlayMusicStream(_music);

    _menu = std::make_unique<Menu>(screenWidth, screenHeight);
    _game = std::make_unique<Game>(screenWidth, screenHeight);
    _gameOver = std::make_unique<GameOver>(screenWidth, screenHeight);
    _victory = std::make_unique<Victory>(screenWidth, screenHeight);
}

void SceneManager::run() {
    while (!WindowShouldClose() && _currentScene != SceneType::EXIT) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsedTime = currentTime - _lastTime;
        _deltaTime = elapsedTime.count();
        _lastTime = currentTime;

        UpdateMusicStream(_music);
        AudioManager::getInstance().updateMusic();

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
        case SceneType::GAME_OVER:
            _currentScene = _gameOver->update(_deltaTime);
            if (_currentScene == SceneType::GAME) {
                _game.reset();
                _game = std::make_unique<Game>(_screenWidth, _screenHeight);
            }
            break;
        case SceneType::VICTORY:
            _currentScene = _victory->update(_deltaTime);
            if (_currentScene == SceneType::GAME) {
                _game.reset();
                _game = std::make_unique<Game>(_screenWidth, _screenHeight);
            }
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
        case SceneType::GAME_OVER:
            _gameOver->draw();
            break;
        case SceneType::VICTORY:
            _victory->draw();
            break;
        case SceneType::EXIT:
            return;
    }
    EndDrawing();
}
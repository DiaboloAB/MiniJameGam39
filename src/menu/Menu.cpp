/*
** EPITECH PROJECT, 2025
** MiniJameGam39
** File description:
** Menu
*/

#include "Menu.hpp"
#include "raylib.h"

Menu::Menu(int screenWidth, int screenHeight)
    : _screenWidth(screenWidth),
      _screenHeight(screenHeight),
      _playButton(610, 550, "assets/button/groupe_button.png",
                  "assets/button/sound-button.wav",
                  "assets/Font/pixantiqua.png", "Play", 4, 2, WHITE),
      _quitButton(1010, 550, "assets/button/groupe_button.png",
                  "assets/button/sound-button.wav",
                  "assets/Font/pixantiqua.png", "Quit", 4, 2, WHITE) {
    _midground = LoadTexture("./assets/paralax/layers/back-buildings.png");
    _background = LoadTexture("./assets/paralax/layers/far-buildings.png");
    _foreground = LoadTexture("./assets/paralax/layers/foreground.png");
}

Menu::~Menu() {
}

SceneType Menu::update(float _deltaTime) {
    _scrollingBack -= 0.2f;
    _scrollingMid -= 1.0f;
    _scrollingFore -= 2.0f;

    if (_scrollingBack <= -_background.width * 5)
        _scrollingBack = 0;
    if (_scrollingMid <= -_midground.width * 5)
        _scrollingMid = 0;
    if (_scrollingFore <= -_foreground.width * 5)
        _scrollingFore = 0;

    if (_playButton.IsClicked()) {
        return SceneType::GAME;
    }
    if (_quitButton.IsClicked()) {
        return SceneType::EXIT;
    }
    return SceneType::MENU;
}

void Menu::draw() {
    DrawTextureEx(_background, (Vector2){_scrollingBack, 20}, 0.0f, 5.0f,
                  WHITE);
    DrawTextureEx(_background,
                  (Vector2){_background.width * 5 + _scrollingBack, 20}, 0.0f,
                  5.0f, WHITE);
    DrawTextureEx(_midground, (Vector2){_scrollingMid, 20}, 0.0f, 5.0f, WHITE);
    DrawTextureEx(_midground,
                  (Vector2){_midground.width * 5 + _scrollingMid, 20}, 0.0f,
                  5.0f, WHITE);
    DrawTextureEx(_foreground, (Vector2){_scrollingFore, 70}, 0.0f, 5.0f,
                  WHITE);
    DrawTextureEx(_foreground,
                  (Vector2){_foreground.width * 5 + _scrollingFore, 70}, 0.0f,
                  5.0f, WHITE);

    DrawText("BRADD PITT SIMULATOR", 320, 440, 100, RED);
    DrawText("BRADD PITT SIMULATOR", 320, 430, 100, WHITE);

    _playButton.Draw();
    _quitButton.Draw();
}
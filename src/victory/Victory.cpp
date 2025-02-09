/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#include "Victory.hpp"
#include "raylib.h"
#include <string>

Victory::Victory(int screenWidth, int screenHeight)
    : _screenWidth(screenWidth),
      _screenHeight(screenHeight),
      _playButton(610, 550, "assets/button/groupe_button.png",
                  "assets/button/sound-button.wav",
                  "assets/Font/pixantiqua.png", "Retry", 4, 2, WHITE),
      _quitButton(1010, 550, "assets/button/groupe_button.png",
                  "assets/button/sound-button.wav",
                  "assets/Font/pixantiqua.png", "Quit", 4, 2, WHITE) {
    _midground = LoadTexture("./assets/paralax/layers/back-buildings.png");
    _background = LoadTexture("./assets/paralax/layers/far-buildings.png");
    _foreground = LoadTexture("./assets/paralax/layers/foreground.png");
}

Victory::~Victory() {
}

SceneType Victory::update(float _deltaTime) {
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
    return SceneType::VICTORY;
}

void Victory::draw() {
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

    std::string gameOver = "YOU WIN";
    int fontSize = 100;
    int textWidth = MeasureText(gameOver.c_str(), fontSize);

    int centerX = _screenWidth / 2 - textWidth / 2 - 30;
    int centerY = 320;

    DrawText(gameOver.c_str(), centerX, centerY, fontSize, RED);
    DrawText(gameOver.c_str(), centerX, centerY - 10, fontSize, WHITE);

    _playButton.Draw();
    _quitButton.Draw();
}
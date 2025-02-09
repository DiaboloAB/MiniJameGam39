/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#include <string>

#include "GameOver.hpp"
#include "raylib.h"

GameOver::GameOver(int screenWidth, int screenHeight)
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

    _timeTexture = LoadTexture("assets/clock.png");
    _bonusTexture = LoadTexture("assets/money.png");
}

GameOver::~GameOver() {
}

SceneType GameOver::update(float _deltaTime) {
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
    return SceneType::GAME_OVER;
}

void GameOver::draw() {
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

    std::string gameOver = "GAME OVER";
    int fontSizeTitle = 100;
    int textWidth = MeasureText(gameOver.c_str(), fontSizeTitle);
    int centerX = _screenWidth / 2 - textWidth / 2;
    int centerY = 250;

    DrawText(gameOver.c_str(), centerX, centerY, fontSizeTitle, RED);
    DrawText(gameOver.c_str(), centerX, centerY - 10, fontSizeTitle, WHITE);

    int totalSeconds = static_cast<int>(GameStats::finalTime);
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;
    std::string timeString =
        (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" +
        (seconds < 10 ? "0" : "") + std::to_string(seconds);

    std::string bonusString = std::to_string(GameStats::finalBonus);

    int fontSizeStats = 40;
    int statsY = centerY + 120;
    int iconSize = 50;
    int spacing = 20;

    int timeWidth = MeasureText(timeString.c_str(), fontSizeStats);
    int bonusWidth = MeasureText(bonusString.c_str(), fontSizeStats);
    int maxStatWidth = std::max(timeWidth, bonusWidth);

    int statsX = _screenWidth / 2 - (maxStatWidth + iconSize + spacing) / 2;

    DrawTextureEx(_timeTexture, {(float)statsX, (float)statsY}, 0.0f, 1.5f,
                  WHITE);
    DrawText(timeString.c_str(), statsX + iconSize + spacing, statsY + 10,
             fontSizeStats, RED);
    DrawText(timeString.c_str(), statsX + iconSize + spacing, statsY + 5,
             fontSizeStats, WHITE);

    DrawTextureEx(_bonusTexture, {(float)statsX, (float)statsY + 70}, 0.0f,
                  1.5f, WHITE);
    DrawText(bonusString.c_str(), statsX + iconSize + spacing, statsY + 80,
             fontSizeStats, RED);
    DrawText(bonusString.c_str(), statsX + iconSize + spacing, statsY + 75,
             fontSizeStats, WHITE);

    _playButton.Draw();
    _quitButton.Draw();
}
/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#include <iostream>

#include "HUD.hpp"
#include "raymath.h"

HUD::HUD() {
    _panicBarTexture = LoadTexture("assets/panicbar.png");
    _panicBarIcon = LoadTexture("assets/heart.png");
    _bonusTexture = LoadTexture("assets/money.png");
    _timeTexture = LoadTexture("assets/clock.png");
    _panel = LoadTexture("assets/hud-panel.png");

    if (_panicBarTexture.id == 0 || _panicBarIcon.id == 0 ||
        _bonusTexture.id == 0 || _timeTexture.id == 0 || _panel.id == 0) {
        throw std::runtime_error("Failed to load HUD textures");
    }

    _panicCount = 0;
    _bonusCount = 0;
    _elapsedTime = 0.0f;
}

HUD::~HUD() {
    // delete _panicBarAnimation;
    // UnloadTexture(_bonusTexture);
}

void HUD::update(float deltaTime, int panic, int bonus) {
    _panicCount = panic;
    _bonusCount = bonus;
    _elapsedTime += deltaTime;
}

void HUD::draw() {
    int startX = 20;                  // Position de départ à gauche
    int spacing = 80;                 // Espacement entre les éléments
    int iconSize = 32;                // Taille des icônes
    int textOffsetX = iconSize + 10;  // Décalage entre l'icône et le texte
    int hudY = 20;                    // Hauteur uniforme

    DrawTextureEx(_panel, {0, 0}, 0.0f, 1.0f, WHITE);

    int totalSeconds = static_cast<int>(_elapsedTime);
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    std::string timeString =
        (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" +
        (seconds < 10 ? "0" : "") + std::to_string(seconds);

    int timeX = startX;
    DrawTextureEx(_timeTexture,
                  {static_cast<float>(timeX), static_cast<float>(hudY)}, 0.0f,
                  1.0f, WHITE);
    DrawText(timeString.c_str(), timeX + textOffsetX, hudY + 5, 20, BLACK);

    int bonusX = timeX + spacing + iconSize;
    DrawTextureEx(
        _bonusTexture,
        {static_cast<float>(bonusX) - 20, static_cast<float>(hudY) - 20}, 0.0f,
        2.0f, WHITE);
    DrawText(std::to_string(_bonusCount).c_str(), bonusX + textOffsetX,
             hudY + 5, 20, BLACK);

    int panicIconX = bonusX + spacing;

    int frameWidth = _panicBarTexture.width / 16;
    Rectangle source = {static_cast<float>(_panicCount * frameWidth), 0,
                        static_cast<float>(frameWidth),
                        static_cast<float>(_panicBarTexture.height)};
    Rectangle dest = {static_cast<float>(panicIconX + textOffsetX),
                      static_cast<float>(hudY + (iconSize / 2) -
                                         (_panicBarTexture.height / 2)),
                      static_cast<float>(frameWidth),
                      static_cast<float>(_panicBarTexture.height)};
    DrawTexturePro(_panicBarTexture, source, dest, {0, 0}, 0.0f, WHITE);
    float cosScaling = cos(_elapsedTime * 10) / 8;
    DrawTextureEx(
        _panicBarIcon,
        {static_cast<float>(panicIconX) + 10, static_cast<float>(hudY) - 20},
        0.0f, 2.5f + cosScaling, WHITE);
}

void HUD::drawTimer(float deltaTime) {
    int totalSeconds = static_cast<int>(deltaTime);
    int milliseconds = static_cast<int>((deltaTime - totalSeconds) * 100);

    std::string timeString = std::to_string(totalSeconds) + "." +
                             (milliseconds < 10 ? "0" : "") +
                             std::to_string(milliseconds);

    int fontSize = 30;
    int textWidth = 40;

    int hudY = 20;

    int centerTextX = 1920 / 2 - 40 / 2;

    DrawText(timeString.c_str(), centerTextX, hudY, fontSize, WHITE);
}

void HUD::reset() {
    _elapsedTime = 0.0f;
    _panicCount = 0;
    _bonusCount = 0;
}
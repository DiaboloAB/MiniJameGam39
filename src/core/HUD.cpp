/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#include "HUD.hpp"

HUD::HUD() {
    Texture2D panicBarTexture = LoadTexture("assets/panicbar.png");
    _panicBarAnimation = new Animation(panicBarTexture, panicBarTexture.width / 6, panicBarTexture.height, 0.1f);
    _bonusTexture = LoadTexture("assets/bonus.png");
    _panicCount = 1;
    _bonusCount = 0;
    _elapsedTime = 0.0f;
}

HUD::~HUD() {
    delete _panicBarAnimation;
    // UnloadTexture(_bonusTexture);
}

void HUD::update(float deltaTime, int panic, int bonus) {
    _panicCount = panic;
    _bonusCount = bonus;
    _elapsedTime += deltaTime;

    _panicBarAnimation->update(deltaTime, _panicCount);
}

void HUD::draw() {
    DrawTexture(_bonusTexture, 10, 10, WHITE);
    DrawText(std::to_string(_bonusCount).c_str(), 50, 10, 20, WHITE);

    _panicBarAnimation->draw({GetScreenWidth() / 2, 10}, 0, 1.0f);

    DrawText(std::to_string(_elapsedTime).c_str(), 10, 50, 20, WHITE);
}
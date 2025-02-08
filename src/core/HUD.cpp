/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#include "HUD.hpp"

HUD::HUD() {
    Texture2D panicBarTexture = LoadTexture("assets/panicbar.png");
    _panicBarAnimation = new Animation(panicBarTexture, panicBarTexture.width / 16, panicBarTexture.height, 0.1f);
    _panicBarTexture = LoadTexture("assets/heart.png");
    _bonusTexture = LoadTexture("assets/bonus.png");
    _timeTexture = LoadTexture("assets/clock.png");
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
    int startX = 20;  // Position de départ à gauche
    int spacing = 100; // Espacement entre les éléments
    int iconSize = 32; // Taille des icônes
    int textOffsetX = iconSize + 10; // Décalage entre l'icône et le texte
    int hudY = 20; // Hauteur uniforme

    int timeX = startX;
    DrawTextureEx(_timeTexture, {static_cast<float>(timeX), static_cast<float>(hudY)}, 0.0f, 1.0f, WHITE);
    DrawText(std::to_string(static_cast<int>(_elapsedTime) / 60).c_str(), timeX + textOffsetX, hudY + 5, 20, BLACK);

    int bonusX = timeX + spacing;
    DrawTextureEx(_bonusTexture, {static_cast<float>(bonusX), static_cast<float>(hudY)}, 0.0f, 1.0f, WHITE);
    DrawText(std::to_string(_bonusCount).c_str(), bonusX + textOffsetX, hudY + 5, 20, BLACK);

    int panicIconX = bonusX + spacing;
    DrawTextureEx(_panicBarTexture, {static_cast<float>(panicIconX), static_cast<float>(hudY)}, 0.0f, 1.0f, WHITE);
    
    int panicBarX = panicIconX + textOffsetX + spacing + textOffsetX / 2;
    _panicBarAnimation->draw({static_cast<float>(panicBarX), static_cast<float>(hudY + (iconSize / 2))}, 0, 1.0f);
}
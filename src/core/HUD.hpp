/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#ifndef HUD_H
#define HUD_H

#include "raylib.h"
#include "Animation.hpp"
#include <vector>
#include <string>

class HUD {
public:
    HUD();
    ~HUD();

    void update(float deltaTime, int panic, int bonus);
    void draw();
    void drawTimer(float deltaTime);

private:
    Animation* _panicBarAnimation;
    Texture2D _panicBarIcon;
    Texture2D _panicBarTexture;
    int _panicCount; // 16 levels of panic
    Texture2D _bonusTexture;
    int _bonusCount;
    Texture2D _timeTexture;
    float _elapsedTime;

    Texture2D _panel;
};

#endif
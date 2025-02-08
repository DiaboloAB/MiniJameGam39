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

private:
    Animation* _panicBarAnimation;
    int _panicCount; // 6 levels of panic
    Texture2D _bonusTexture;
    int _bonusCount;
    float _elapsedTime;
};

#endif
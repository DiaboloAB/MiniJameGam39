/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#ifndef ANIMATION_H
#define ANIMATION_H

 #include "raylib.h"
 #include <vector>

 class Animation {
    public:
        Animation(Texture2D texture, int frameWidth, int frameHeight, float frameTime);
        ~Animation();
    
        void update(float deltaTime, int frames);
        void draw(Vector2 position, int direction, float scale);

    private:
        Texture2D _texture;
        int _frameWidth;
        int _frameHeight;
        float _frameTime;
        float _elapsedTime;
        int _currentFrame;
 };

#endif
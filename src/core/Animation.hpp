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
        Animation(Texture2D texture, int frameWidth, int frameHeight, float frameTime, float speed);
        ~Animation();
    
        void update(float deltaTime);
        void draw(Vector2 position, float rotation = 0.0f);

    private:
        Texture2D _texture;
        int _frameWidth;
        int _frameHeight;
        float _frameTime;
        float _speed;
        float _elapsedTime;
        int _currentFrame;
 };

#endif
/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#ifndef PLAYER_H
#define PLAYER_H

// std
#include "raylib.h"

class Player {
public:
    Player();
    ~Player();

    void move(Vector2 direction);
    Vector2 getPosition() {
        return _position;
    }
    void update(float deltaTime);
    void draw();

private:
    Vector2 _position;
    Texture2D _texture;
    int _frameHeight;
    int _frameWidth;
    float _frameTime;
    float _timer;
    int _currentFrame;
    int _direction; // 0: down, 1: left, 2: right, 3: up
};

#endif  // PLAYER_H
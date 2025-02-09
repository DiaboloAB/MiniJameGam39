/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#ifndef PLAYER_H
#define PLAYER_H

// std
#include <iostream>

#include "../core/Animation.hpp"
#include "raylib.h"

class Player {
public:
    Player();
    ~Player();

    void move(Vector2 direction);
    Vector2 getPosition() {
        return _position;
    }

    void setPosition(Vector2 position) {
        _position = position;
    }
    void update(float deltaTime);

    Rectangle getBoundingBox();

    void draw();
    int getPanic() {
        return _panic;
    }
    int getBonus() {
        return _bonus;
    }

    bool getIsDriving() {
        return _isDriving;
    }

    void setIsDriving(bool isDriving) {
        _isDriving = isDriving;
    }

    float getSpeed() {
        return _speed;
    }

    void setSpeed(float speed) {
        _speed = speed;
    }

    float _panic;  // 16 levels of panic
private:
    Vector2 _position;
    Animation* _animation;
    int _direction;  // 0: Left, 1: Down, 2: Up, 3: Right
    bool _isMoving;
    int _bonus;
    bool _isDriving = false;
    float _speed = 400;
};

#endif  // PLAYER_H
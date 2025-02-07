/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#ifndef PLAYER_H
#define PLAYER_H

// std
#include "raylib.h"
#include <iostream>
#include "../core/Animation.hpp"

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
    Animation* _animation;
    int _direction; // 0: Left, 1: Down, 2: Up, 3: Right
    bool _isMoving;
};

#endif  // PLAYER_H
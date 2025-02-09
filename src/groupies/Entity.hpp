/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>

#include "../core/Animation.hpp"
#include "player/Player.hpp"
#include "raylib.h"
#include "raymath.h"
#include "world/World.hpp"

class Entity {
public:
    Entity();
    ~Entity();

    void move(Vector2 direction);
    Vector2 getPosition() {
        return _position;
    }

    void setPosition(Vector2 position) {
        _position = position;
    }
    bool update(float deltaTime, Player* player, World* world);

    Rectangle getBoundingBox();

    Rectangle getTinyBoundingBox();

    void draw();

private:
    Vector2 _position;
    Animation* _animation;
    int _direction;  // 0: Left, 1: Down, 2: Up, 3: Right
    bool _isMoving;
};

#endif  // ENTITY_H
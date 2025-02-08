/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#ifndef CAR_H
#define CAR_H

#include "raylib.h"
#include "../core/Animation.hpp"
#include <stdexcept>
#include <cmath>

class Car {
public:
    Car();
    ~Car();

    void update(float deltaTime);
    void draw();
    void accelerate(float amount);
    void turn(float angle);
    Vector2 getPosition() {
        return _position;
    }

private:
    Vector2 _position;
    Animation* _animation;
    float _angle;
    float _speed;

    int _direction;
    int getDirectionFromAngle();
};

#endif  // CAR_H
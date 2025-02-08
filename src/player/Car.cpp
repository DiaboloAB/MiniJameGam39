/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#include "Car.hpp"

Car::Car() {
    _position = {100, 0};
    Texture2D texture = LoadTexture("assets/car.png");
    if (texture.id == 0) {
        throw std::runtime_error("Failed to load car texture");
    }
    _animation = new Animation(texture, texture.width / 4, texture.height / 3, 0.1f);
    _angle = 0.0f;
    _speed = 0.0f;
    _direction = 0;
}

Car::~Car() {
    delete _animation;
}

void Car::update(float deltaTime) {
    if (_speed != 0) {
        _position.x += std::cos(_angle * DEG2RAD) * _speed * deltaTime;
        _position.y += std::sin(_angle * DEG2RAD) * _speed * deltaTime;

        _speed *= 0.98f;  // Ajout de friction pour ralentir progressivement
        if (fabs(_speed) < 0.1f) {
            _speed = 0;
        }
    }

    _direction = getDirectionFromAngle();
    if (_speed != 0) {
        _animation->update(deltaTime, 3);
    }
}

int Car::getDirectionFromAngle() {
    if ((_angle >= 315 || _angle < 45)) return 0; // Avant
    if (_angle >= 45 && _angle < 135) return 1;   // Droite
    if (_angle >= 135 && _angle < 225) return 2;  // Bas
    if (_angle >= 225 && _angle < 315) return 3;  // Gauche
    return 0; // Par défaut
}

void Car::accelerate(float amount) {
    _speed += amount;
}

void Car::turn(float angle) {
    if (_speed != 0) {  // Ne tourne que si la voiture est en mouvement
        _angle += angle;
        if (_angle >= 360) {
            _angle -= 360;
        } else if (_angle < 0) {
            _angle += 360;
        }
    }
}

void Car::draw() {
    _animation->draw(_position, _direction, 4.0f);
}

Rectangle Car::getBoundingBox() {
    return {_position.x - 25, _position.y - 25, 50, 50};
}
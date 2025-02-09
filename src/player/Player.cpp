/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#include "Player.hpp"

Player::Player() {
    _position = {64, 64};
    Texture2D texture = LoadTexture("assets/player.png");
    if (texture.id == 0) {
        throw std::runtime_error("Failed to load player texture");
    }
    _animation =
        new Animation(texture, texture.width / 4, texture.height / 3, 0.1f);
    _direction = 0;
    _panic = 0;
    _bonus = 0;
}

Player::~Player() {
    delete _animation;
}

void Player::move(Vector2 direction) {
    _isMoving = (direction.x != 0 || direction.y != 0);

    // _position.x += direction.x;
    // _position.y += direction.y;

    if (direction.x > 0) {
        _direction = 3;  // Right
    } else if (direction.x < 0) {
        _direction = 0;  // Left
    } else if (direction.y > 0) {
        _direction = 1;  // Down
    } else if (direction.y < 0) {
        _direction = 2;  // Up
    }
}

void Player::update(float deltaTime) {
    if (_speed > 430)
        _speed = 430;
    if (_speed < 400)
        _speed += deltaTime;
    if (_speed > 400)
        _speed -= deltaTime;
    if (_speed > 395 && _speed < 405)
        _speed = 400;

    if (_isMoving) {
        _animation->update(deltaTime, 3);
    } else {
        _animation->update(deltaTime, 1);
    }
}

void Player::draw() {
    _animation->draw(_position, _direction, 4.0f);
}

Rectangle Player::getBoundingBox() {
    return {_position.x - 25, _position.y - 25, 50, 50};
}

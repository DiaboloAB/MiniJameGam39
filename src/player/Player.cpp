/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#include "Player.hpp"

Player::Player() {
    _position = {0, 0};
    _texture = LoadTexture("assets/player.png");
    if (_texture.id == 0) {
        throw std::runtime_error("Failed to load player texture");
    }
    _frameHeight = _texture.height / 4;
    _frameWidth = _texture.width / 4;
    _currentFrame = 0;
    _frameTime = 0.1f;
    _timer = 0.0f;
    _direction = 0;
}

Player::~Player() {
    UnloadTexture(_texture);
}

void Player::move(Vector2 direction) {
    _position.x += direction.x;
    _position.y += direction.y;

    if (direction.x > 0) {
        _direction = 2;
    } else if (direction.x < 0) {
        _direction = 1;
    } else if (direction.y > 0) {
        _direction = 0;
    } else if (direction.y < 0) {
        _direction = 3;
    }
}

void Player::update(float deltaTime) {
    _timer += deltaTime;
    if (_timer >= _frameTime) {
        _currentFrame = (_currentFrame + 1) % 4;
        _timer = 0.0f;
    }
}

void Player::draw() {

    Rectangle source = {
        static_cast<float>(_currentFrame * _frameWidth),
        static_cast<float>(_direction * _frameHeight),
        static_cast<float>(_frameWidth),
        static_cast<float>(_frameHeight)
    };

    Rectangle dest = {
        _position.x,
        _position.y,
        static_cast<float>(_frameWidth),
        static_cast<float>(_frameHeight)
    };
    DrawTexturePro(_texture, source, dest, {0, 0}, 0.0f, WHITE);
}

/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#include "Animation.hpp"

Animation::Animation(Texture2D texture, int frameWidth, int frameHeight, float frameTime) {
    _texture = texture;
    _frameWidth = frameWidth;
    _frameHeight = frameHeight;
    _frameTime = frameTime;
    _elapsedTime = 0.0f;
    _currentFrame = 0;
}

Animation::~Animation() {
    UnloadTexture(_texture);
}

void Animation::update(float deltaTime, int frames) {
    _elapsedTime += deltaTime;
    if (_elapsedTime >= _frameTime) {
        _currentFrame = (_currentFrame + 1) % frames;
        _elapsedTime = 0.0f;
    }
}

void Animation::draw(Vector2 position, int direction, float scale) {
    Rectangle source = {
        static_cast<float>(direction * _frameWidth),
        static_cast<float>(_currentFrame * _frameHeight),
        static_cast<float>(_frameWidth),
        static_cast<float>(_frameHeight)
    };

    Rectangle dest = {
        position.x,
        position.y,
        static_cast<float>(_frameWidth) * scale,
        static_cast<float>(_frameHeight) * scale
    };

    DrawTexturePro(_texture, source, dest, {0, 0}, 0, WHITE);
}
/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#include "Game.hpp"
#include "raymath.h"

// std
#include <iostream>

void Game::initCamera() {
    _camera.target = (Vector2){0, 0};
    _camera.offset = {(float)_screenWidth / 2, (float)_screenHeight / 2};
    _camera.rotation = 0.0f;
    _camera.zoom = 1.0f;
}

void Game::followPlayer() {
    // the camera move if the player is too far from the center of the screen

    float horizontalOffset = 500;
    float verticalOffset = 225;

    Vector2 playerScreenPos =
        GetWorldToScreen2D(_player->getPosition(), _camera);
    Vector2 cameraCenter = {(float)_screenWidth / 2, (float)_screenHeight / 2};

    Vector2 distance = Vector2Subtract(playerScreenPos, cameraCenter);

    Vector2 lerpV = (Vector2){0, 0};
    if (fabs(distance.x) > horizontalOffset)
        lerpV.x = distance.x > 0 ? distance.x - horizontalOffset
                                 : distance.x + horizontalOffset;
    if (fabs(distance.y) > verticalOffset)
        lerpV.y = distance.y > 0 ? distance.y - verticalOffset
                                 : distance.y + verticalOffset;
    _camera.target = Vector2Lerp(_camera.target, _camera.target + lerpV, 0.1f);
}
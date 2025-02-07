/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#include "Player.hpp"

Player::Player() {
    _position = {0, 0};
    // Constructor implementation
}

Player::~Player() {
    // Destructor implementation
}

void Player::move(Vector2 direction) {
    _position.x += direction.x;
    _position.y += direction.y;
}

void Player::draw() {
    DrawRectangle(_position.x - 25, _position.y - 25, 50, 50, RED);
}
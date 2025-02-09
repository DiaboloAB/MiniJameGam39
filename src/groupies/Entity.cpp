/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#include "Entity.hpp"

Entity::Entity() {
    _position = {0, 0};
    int random = GetRandomValue(1, 5);
    Texture2D texture =
        LoadTexture(("assets/fan" + std::to_string(random) + ".png").c_str());
    if (texture.id == 0) {
        throw std::runtime_error("Failed to load Entity texture");
    }
    _animation =
        new Animation(texture, texture.width / 4, texture.height / 3, 0.1f);
    _direction = 0;
}

Entity::~Entity() {
    delete _animation;
}

void Entity::move(Vector2 direction) {
    _isMoving = (direction.x != 0 || direction.y != 0);

    // _position.x += direction.x;
    // _position.y += direction.y;

    if (direction.x > 0.5) {
        _direction = 3;  // Right
    } else if (direction.x < -0.5) {
        _direction = 0;  // Left
    } else if (direction.y > 0.5) {
        _direction = 1;  // Down
    } else if (direction.y < -0.5) {
        _direction = 2;  // Up
    }
}

bool Entity::update(float deltaTime, Player* player, World* world) {
    Vector2 direction = {0, 0};
    float speed = 400 * deltaTime;

    direction.x = player->getPosition().x - _position.x;
    direction.y = player->getPosition().y - _position.y;

    float distance = Vector2Distance(player->getPosition(), _position);

    if (player->getIsDriving() && distance < 20)
        return true;

    if (distance < 5) {
        return false;
    }

    if (Vector2Length(direction) > 0) {
        direction = Vector2Normalize(direction);
        direction = Vector2Scale(direction, speed);

        move(direction);

        Vector2 newPosition = getPosition();
        newPosition.x += direction.x;
        setPosition(newPosition);

        Rectangle playerBoundingBox = getBoundingBox();
        Rectangle collision = world->getCollisions(playerBoundingBox);

        if (collision.width != 0 && collision.height != 0) {
            newPosition.x -= direction.x;
            setPosition(newPosition);
        }

        newPosition = getPosition();
        newPosition.y += direction.y;
        setPosition(newPosition);

        playerBoundingBox = getBoundingBox();
        collision = world->getCollisions(playerBoundingBox);

        if (collision.width != 0 && collision.height != 0) {
            newPosition.y -= direction.y;
            setPosition(newPosition);
        }

        _animation->update(deltaTime, 3);
    }
    return false;
}

void Entity::draw() {
    _animation->draw(_position, _direction, 4.0f);
}

Rectangle Entity::getBoundingBox() {
    return {_position.x - 25, _position.y - 25, 50, 50};
}

Rectangle Entity::getTinyBoundingBox() {
    return {_position.x - 10, _position.y - 10, 20, 20};
}
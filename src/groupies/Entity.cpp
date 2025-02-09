/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#include "Entity.hpp"
#include "core/AudioManager.hpp"

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
    _emojis = LoadTexture("assets/emojis.png");
    _direction = 0;
}

Entity::~Entity() {
    delete _animation;
}

void Entity::move(Vector2 direction) {
    _isMoving = (direction.x != 0 || direction.y != 0);
    if (!_following)
        _isMoving = false;

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
    float speed = 360 * deltaTime;

    if (_state != 0) {
        _emojiTime += deltaTime;
        if (_emojiTime > 1.5)
            _state = 0;
    }

    direction.x = player->getPosition().x - _position.x;
    direction.y = player->getPosition().y - _position.y;

    float distance = Vector2Distance(player->getPosition(), _position);

    if (!_following && distance < 300) {
        if (!_satisfied) {
            AudioManager::getInstance().playFootStep();
            _following = true;
            setEmoji(1);
        }
    }

    if ((player->_drivingMode && distance < 40) || (distance > 6000))
        return true;

    if (distance < 25) {
        if (!_satisfied) {
            _satisfied = true;
            _following = false;
            player->_panic += 2;
            player->setSpeed(350);
            setEmoji(2);
        }
        return false;
    }

    if (Vector2Length(direction) > 0) {
        direction = Vector2Normalize(direction);
        direction = Vector2Scale(direction, speed);
        move(direction);

        Vector2 newPosition = getPosition();
        if (_following)
            newPosition.x += direction.x;
        setPosition(newPosition);

        Rectangle playerBoundingBox = getBoundingBox();
        Rectangle collision = world->getCollisions(playerBoundingBox);

        if (collision.width != 0 && collision.height != 0) {
            newPosition.x -= direction.x;
            setPosition(newPosition);
        }

        newPosition = getPosition();
        if (_following)
            newPosition.y += direction.y;
        setPosition(newPosition);

        playerBoundingBox = getBoundingBox();
        collision = world->getCollisions(playerBoundingBox);

        if (collision.width != 0 && collision.height != 0) {
            newPosition.y -= direction.y;
            setPosition(newPosition);
        }

        if (_isMoving) {
            _animation->update(deltaTime, 3);
        } else {
            _animation->update(deltaTime, 1);
        }
    }
    return false;
}

void Entity::draw() {
    _animation->draw(_position, _direction, 4.0f);

    float scaleFactor = 2.0f;
    Vector2 emojiPosition = {
        _position.x - 16,
        _position.y - 50 -
            (int)(_emojiTime * 5)};  // Adjust the offset as needed

    // Define the size of each emoji in the texture
    int emojiSize = 16;  // Assuming each emoji is 32x32 pixels
    // Calculate the source rectangle for the emoji
    Rectangle sourceRect = {static_cast<float>(_state * emojiSize), 0,
                            static_cast<float>(emojiSize),
                            static_cast<float>(emojiSize)};

    Rectangle destRect = {emojiPosition.x, emojiPosition.y,
                          emojiSize * scaleFactor, emojiSize * scaleFactor};

    // Draw the emoji rectangle
    DrawTexturePro(_emojis, sourceRect, destRect, (Vector2){0, 0}, 0.0f,
                   WHITE);  // Adjust the emoji texture and size as needed
}

Rectangle Entity::getBoundingBox() {
    return {_position.x - 25, _position.y - 25, 50, 50};
}

Rectangle Entity::getTinyBoundingBox() {
    return {_position.x - 10, _position.y - 10, 20, 20};
}

void Entity::setEmoji(int nb) {
    _emojiTime = 0;
    _state = nb;
}
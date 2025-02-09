/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#include "BonusManager.hpp"
#include "core/AudioManager.hpp"
#include "iostream"
#include "raymath.h"

BonusManager::BonusManager() {
    _car = LoadTexture("assets/car.png");
    _money = LoadTexture("assets/money.png");
    // Constructor implementation
}

BonusManager::~BonusManager() {
    // Destructor implementation
}

void BonusManager::addBonus(const Bonus& bonus) {
    std::cout << "addBonus" << std::endl;
    _bonuses.push(bonus);
}

void BonusManager::update(float deltaTime, Player* player) {
    _elapsedTime += deltaTime;
    float distance = 0;
    int passed = _bonuses.size();

    while (passed != 0) {
        Bonus bonus = _bonuses.front();
        _bonuses.pop();

        bonus.timer += deltaTime;
        distance = Vector2Length(
            Vector2Subtract(bonus.position, player->getPosition()));

        if (distance < 40 && bonus.timer > 1) {
            activateBonus(bonus.name, player);
        } else {
            _bonuses.push(bonus);
        }

        passed--;
    }
}

void BonusManager::activateBonus(BonusName name, Player* player) {
    switch (name) {
        case BonusName::CAR:
            AudioManager::getInstance().startCar();
            player->_drivingMode = true;
            player->_drivingTimer = 6.0f;
            break;
        case BonusName::MONEY:
            AudioManager::getInstance().playCoin();
            player->_panic--;
            player->setSpeed(player->getSpeed() + 10);
            player->addBonus();
            break;
    }
}

void BonusManager::draw() {
    std::queue<Bonus> tempQueue = _bonuses;
    float cosM = cos(_elapsedTime * 10) * 5;

    while (!tempQueue.empty()) {
        Bonus bonus = tempQueue.front();
        tempQueue.pop();

        switch (bonus.name) {
            case BonusName::CAR:
                DrawTexturePro(
                    _car, (Rectangle){0, 0, 32, 32},
                    (Rectangle){bonus.position.x, bonus.position.y, 128, 128},
                    (Vector2){64, 64}, 0, WHITE);
                break;
            case BonusName::MONEY:
                DrawTextureEx(_money,
                              (Vector2){bonus.position.x - 32,
                                        bonus.position.y - 32 + cosM},
                              0, 2, WHITE);
                break;
        }
    }
}
// Bonus
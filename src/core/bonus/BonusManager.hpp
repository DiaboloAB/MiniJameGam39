/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#ifndef BONUSMANAGER_H
#define BONUSMANAGER_H

#include <queue>  // Include the queue header
#include <vector>

#include "player/Player.hpp"
#include "raylib.h"
// std

enum class BonusName {
    CAR,
    MONEY,
    NONE
    // Add more bonus names as needed
};

struct Bonus {
    BonusName name;
    Vector2 position;
};

class BonusManager {
public:
    BonusManager();
    ~BonusManager();

    // Getters

    // Setters
    void addBonus(const Bonus& bonus);

    void draw();
    void update(float deltaTime, Player* player);
    void activateBonus(BonusName name, Player* player);

private:
    std::queue<Bonus> _bonuses;
    Texture2D _car;
    Texture2D _money;

    float _elapsedTime = 0;
};

#endif  // BONUSMANAGER_H
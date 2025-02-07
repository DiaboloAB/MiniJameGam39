/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#ifndef PLAYER_H
#define PLAYER_H

// std
#include "raylib.h"

class Player {
public:
    Player();
    ~Player();

    void move(Vector2 direction);
    Vector2 getPosition() {
        return _position;
    }

    void draw();

private:
    Vector2 _position;
};

#endif  // PLAYER_H
/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#ifndef GAME_H
#define GAME_H

// std
#include <chrono>

class Game {
public:
    Game(int screenWidth = 800, int screenHeight = 450);
    ~Game();

    void run();
    void update(float deltaTime);
    void draw();

private:
    float _deltaTime;
    std::chrono::high_resolution_clock::time_point _lastTime;

    int _screenWidth;
    int _screenHeight;
};

#endif  // GAME_H
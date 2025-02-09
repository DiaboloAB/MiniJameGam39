/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "./Pathfinding/pathfinding.hpp"
#include "./menu/Menu.hpp"
#include "./scene/SceneManager.hpp"
#include "core/Game.hpp"
#include "raylib.h"

int main() {
    std::srand(static_cast<unsigned int>(
        std::time(nullptr)));  // Seed the random number generator
    SceneManager scene = SceneManager(1920, 1080);
    scene.run();
    return 0;
}
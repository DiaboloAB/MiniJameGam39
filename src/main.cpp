/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#include "core/Game.hpp"
#include "raylib.h"

int main() {
    Game game = Game(1920, 1080);

    game.run();

    return 0;
}
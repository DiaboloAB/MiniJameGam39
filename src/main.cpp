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
    // load image
    // Image img = LoadImage("assets/test.jpg");

    // while (!WindowShouldClose()) {
    //     BeginDrawing();

    //     ClearBackground(RAYWHITE);

    //     DrawText("Congrats! You created your first window!", 190, 200, 20,
    //              LIGHTGRAY);

    //     DrawTexture(LoadTextureFromImage(img), 0, 0, WHITE);

    //     EndDrawing();
    // }

    return 0;
}
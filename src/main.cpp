/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#include "raylib.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight,
               "raylib [core] example - basic window");

    SetTargetFPS(60);
    // raylib debug off
    SetTraceLogLevel(LOG_NONE);

    // load image
    Image img = LoadImage("assets/test.jpg");

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20,
                 LIGHTGRAY);

        DrawTexture(LoadTextureFromImage(img), 0, 0, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
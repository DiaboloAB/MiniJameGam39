/*
** EPITECH PROJECT, 2025
** MiniJameGam39
** File description:
** Menu
*/

#include "Menu.hpp"
#include "raylib.h"
#include "button/button.hpp"

Menu::Menu()
{
}

Menu::~Menu()
{
}

int Menu::paralax(int screenWidth, int screenHeight)
{

    Texture2D midground = LoadTexture("./assets/paralax/layers/back-buildings.png");
    Texture2D  background= LoadTexture("./assets/paralax/layers/far-buildings.png");
    Texture2D foreground = LoadTexture("./assets/paralax/layers/foreground.png");

    float scrollingBack = 0.0f;
    float scrollingMid = 0.0f;
    float scrollingFore = 0.0f;
    Button playButton(610, 550, "assets/button/groupe_button.png", "assets/button/sound-button.wav", "assets/Font/pixantiqua.png", "Play", 4, 2, WHITE);
    Button quitButton(1010, 550, "assets/button/groupe_button.png", "assets/button/sound-button.wav", "assets/Font/pixantiqua.png", "Quit", 4, 2, WHITE);

    while (!WindowShouldClose())
    {
        scrollingBack -= 0.2f;
        scrollingMid -= 1.0f;
        scrollingFore -= 2.0f;

        if (scrollingBack <= -background.width * 5) scrollingBack = 0;
        if (scrollingMid <= -midground.width * 5) scrollingMid = 0;
        if (scrollingFore <= -foreground.width * 5) scrollingFore = 0;
        

        BeginDrawing();

            ClearBackground(GetColor(0x052c46ff));

            DrawTextureEx(background, (Vector2){ scrollingBack, 20 }, 0.0f, 5.0f, WHITE);
            DrawTextureEx(background, (Vector2){ background.width*5 + scrollingBack, 20 }, 0.0f, 5.0f, WHITE);

            DrawTextureEx(midground, (Vector2){ scrollingMid, 20 }, 0.0f, 5.0f, WHITE);
            DrawTextureEx(midground, (Vector2){ midground.width*5 + scrollingMid, 20 }, 0.0f, 5.0f, WHITE);

            DrawTextureEx(foreground, (Vector2){ scrollingFore, 70 }, 0.0f, 5.0f, WHITE);
            DrawTextureEx(foreground, (Vector2){ foreground.width*5 + scrollingFore, 70 }, 0.0f, 5.0f, WHITE);

            DrawText("(c) Cyberpunk Street Environment by Luis Zuno (@ansimuz)", 10, 10, 20, RED);
            DrawText("Game made by Alexis Boitel, Justine Loizel, Augustin", 10, 980, 20, RED);
            DrawText("Game made by Alexis Boitel, Justine Loizel, Augustin", 10, 978, 20, WHITE);

            DrawText("BRADD PITT SIMULATOR", 320, 440, 100, RED);
            DrawText("BRADD PITT SIMULATOR", 320, 430, 100, WHITE);

            playButton.Draw();
            quitButton.Draw();
        EndDrawing();
    }

    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);

    CloseWindow();

    return 0;
}

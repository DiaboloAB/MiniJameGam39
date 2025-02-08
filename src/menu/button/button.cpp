#include "button.hpp"
#include "raylib.h"

#define NUM_FRAMES  3  // Nombre de frames dans la texture
#define RAYORANGE  CLITERAL(Color){ 255, 223, 134, 255 }
#define DARKORANGE  CLITERAL(Color){ 170, 150, 130, 255 }

Button::Button(float x, float y, const char* pathTextureButton, const char* pathfxButton, const char* pathFont, const char *textButtonparam, float fontSizeparam, float spacingLettersparam, Color colorButtonparam)
{
    button = LoadTexture(pathTextureButton);
    fxButton = LoadSound(pathfxButton);
    font = LoadFont(pathFont);


    textButton = textButtonparam;
    fontSize = fontSizeparam;
    spacingLetters = spacingLettersparam;
    colorButton = colorButtonparam;

    float frameHeight = (float)button.height / NUM_FRAMES;

    btnBounds = { x, y, (float)button.width, frameHeight };

    sourceRec = { 0, 0, (float)button.width, frameHeight };
    btnState = 0;
    btnAction = false;
}

void Button::Draw()
{
    Vector2 mousePoint = GetMousePosition();
    btnAction = false;

    if (CheckCollisionPointRec(mousePoint, btnBounds))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            btnState = 0;
            colorButton = DARKGRAY;
        }
        else {
            btnState = 2;
            colorButton = DARKORANGE;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            btnAction = true;
            PlaySound(fxButton);
        }
    }
    else {
        btnState = 1;
        colorButton = RAYORANGE;
    }

    sourceRec.y = btnState * btnBounds.height;

    DrawTextureRec(button, sourceRec, (Vector2){ btnBounds.x, btnBounds.y }, WHITE);
    DrawTextEx(font, textButton, (Vector2){btnBounds.x + button.width / 3, btnBounds.y + button.height / 12}, font.baseSize*fontSize, spacingLetters,  colorButton); 
}

Button::~Button()
{
    UnloadTexture(button);
    UnloadSound(fxButton);
}

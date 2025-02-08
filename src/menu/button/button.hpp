#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "raylib.h"

class Button {
public:
    Button(float x, float y, const char* pathTextureButton, const char* pathfxButton,
        const char* pathFont, const char *textButton, float fontSize, float spacingLetters, Color colorButton);
    ~Button();

    void Draw();
    bool IsClicked();


private:
    Texture2D button;
    Sound fxButton;
    Rectangle sourceRec;
    Rectangle btnBounds;
    Font font;

    const char *textButton;
    float fontSize;
    float spacingLetters;
    Color colorButton;

    int btnState;
    bool btnAction;
};

#endif

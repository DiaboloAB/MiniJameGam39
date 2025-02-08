/*
** EPITECH PROJECT, 2025
** MiniJameGam39
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include "button/button.hpp"
#include "scene/SceneType.hpp"

class Menu {
public:
    Menu(int screenWidth = 1920, int screenHeight = 1080);
    ~Menu();
    SceneType update(float _deltaTime);
    void draw();

private:
    Texture2D _midground;
    Texture2D _background;
    Texture2D _foreground;

    Button _playButton;
    Button _quitButton;

    float _scrollingBack = 0.0f;
    float _scrollingMid = 0.0f;
    float _scrollingFore = 0.0f;

    int _screenWidth;
    int _screenHeight;
};

#endif /* !MENU_HPP_ */

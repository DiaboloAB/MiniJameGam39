/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#ifndef GAMEOVER_HPP_
#define GAMEOVER_HPP_

#include "../menu/button/button.hpp"
#include "scene/SceneType.hpp"

class GameOver {
public:
    GameOver(int screenWidth = 1920, int screenHeight = 1080);
    ~GameOver();
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

#endif /* !GAMEOVER_HPP_ */
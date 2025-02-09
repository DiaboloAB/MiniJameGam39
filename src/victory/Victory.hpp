/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#ifndef VICTORY_HPP_
#define VICTORY_HPP_

#include "../menu/button/button.hpp"
#include "scene/SceneType.hpp"

class Victory {
public:
    Victory(int screenWidth = 1920, int screenHeight = 1080);
    ~Victory();
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

#endif /* !VICTORY_HPP_ */
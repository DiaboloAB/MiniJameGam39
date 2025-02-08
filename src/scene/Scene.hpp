#ifndef SCENE_HPP_
#define SCENE_HPP_

#include "raylib.h"
#include "../core/Game.hpp"

// Déclarations avancées pour éviter l'inclusion circulaire
class Menu;
enum class SceneType {
    MENU,
    GAME,
    EXIT
};

class SceneManager {
public:
    SceneManager(int screenWidth, int screenHeight)
        : _screenWidth(screenWidth), _screenHeight(screenHeight), _currentScene(SceneType::MENU) {
        InitAudioDevice();
        InitWindow(screenWidth, screenHeight, "Brad Pitt Simulator");
        SetTargetFPS(60);

    }   
    
    ~SceneManager() {
        CloseAudioDevice();
        CloseWindow();
    }
    
    void run() {
        while (!WindowShouldClose() && _currentScene != SceneType::EXIT) {
            std::cout << "COOOL CA VAS LA" << std::endl;

            switch (_currentScene) {
                case SceneType::MENU:
                    std::cout << "COOOL MENU" << std::endl;
                    runMenu();
                    break;
                case SceneType::GAME:
                    std::cout << "COOOL GAME" << std::endl;

                    runGame();
                    break;
                case SceneType::EXIT:
                    std::cout << "COOOL EXIT" << std::endl;

                    return;
            }
        }
    }

private:
    int _screenWidth;
    int _screenHeight;
    SceneType _currentScene;

    void runMenu();
    void runGame();
};

#endif /* !SCENE_HPP_ */

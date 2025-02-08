/*
** EPITECH PROJECT, 2025
** MiniJameGam39
** File description:
** Scene
*/

#include "Scene.hpp"
#include "../menu/Menu.hpp"


void SceneManager::runMenu() {
    Menu menu;
    _currentScene = menu.paralax(_screenWidth, _screenHeight);
}

void SceneManager::runGame() {
    Game game;
    _currentScene = game.run();
}
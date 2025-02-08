/*
** EPITECH PROJECT, 2025
** MiniJameGam39
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

enum class SceneType;

class Menu {
    public:
        Menu();
        ~Menu();
        SceneType paralax(int screenWidth, int screenHeight);
};

#endif /* !MENU_HPP_ */

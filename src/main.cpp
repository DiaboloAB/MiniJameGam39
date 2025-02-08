/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#include "core/Game.hpp"
#include "raylib.h"
#include "./Pathfinding/pathfinding.hpp"
#include <iostream>
#include "./menu/Menu.hpp"
#include "./scene/Scene.hpp"


int main() {
    SceneManager scene  = SceneManager(1920,1080);
    scene.run();



    // AStar::Generator generator;
    // generator.setWorldSize({25, 25});
    // generator.setHeuristic(AStar::Heuristic::euclidean);
    // generator.setDiagonalMovement(true);

    // std::cout << "Generate path ... \n";
    // auto path = generator.findPath({0, 0}, {20, 20});

    // for(auto& coordinate : path) {
    //     std::cout << coordinate.x << " " << coordinate.y << "\n";
    // }
    return 0;
}
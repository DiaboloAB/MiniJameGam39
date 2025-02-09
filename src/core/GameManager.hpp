/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "groupies/EntityManager.hpp"
#include "player/Player.hpp"
#include "world/World.hpp"
// std

class GameManager {
public:
    GameManager(World *world, EntityManager *entityManager, Player *player);
    ~GameManager();

    // Methods
    void update(float deltaTime, Vector2 camTopLeft, Vector2 screenSize);

    // Getters

    // Setters

private:
    float _spawnTimer;

    EntityManager *_entityManager;
    World *_world;
    Player *_player;
    // Member variables
};

#endif  // GAMEMANAGER_H
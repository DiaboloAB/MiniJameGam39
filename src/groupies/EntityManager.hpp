/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <memory>
#include <queue>
#include <unordered_map>

#include "Entity.hpp"

class EntityManager {
public:
    EntityManager();
    ~EntityManager();

    int spawnEntity(Vector2 position);
    void killEntity(int id);

    void update(float deltaTime, Player *player, World *world,
                BonusManager *bonusManager);

    void handleCollision(Entity *entity1, Entity *entity2);

    void draw();

private:
    std::unordered_map<int, std::unique_ptr<Entity>> _entities;
    size_t _nextId = 0;
    std::queue<int> _killQueue;
};

#endif  // ENTITYMANAGER_H
/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#include "EntityManager.hpp"

EntityManager::EntityManager() {
    _entities = std::unordered_map<int, std::unique_ptr<Entity>>();
}

EntityManager::~EntityManager() {
    // Destructor implementation
}

void EntityManager::killEntity(int id) {
    _killQueue.push(id);
}

int EntityManager::spawnEntity(Vector2 position) {
    std::cout << "spawn entity:" << _nextId << std::endl;
    _entities[_nextId] = std::make_unique<Entity>();
    _entities[_nextId]->setPosition(position);
    return _nextId++;
}

void EntityManager::handleCollision(Entity* entity1, Entity* entity2) {
    Rectangle entity1BoundingBox = entity1->getTinyBoundingBox();
    Rectangle entity2BoundingBox = entity2->getTinyBoundingBox();

    if (CheckCollisionRecs(entity1BoundingBox, entity2BoundingBox)) {
        Rectangle intersection =
            GetCollisionRec(entity1BoundingBox, entity2BoundingBox);

        // move only entity1 out of intersection
        if (intersection.width < intersection.height) {
            if (entity1BoundingBox.x < entity2BoundingBox.x) {
                entity1->setPosition(
                    {entity1->getPosition().x - intersection.width,
                     entity1->getPosition().y});
            } else {
                entity1->setPosition(
                    {entity1->getPosition().x + intersection.width,
                     entity1->getPosition().y});
            }
        } else {
            if (entity1BoundingBox.y < entity2BoundingBox.y) {
                entity1->setPosition(
                    {entity1->getPosition().x,
                     entity1->getPosition().y - intersection.height});
            } else {
                entity1->setPosition(
                    {entity1->getPosition().x,
                     entity1->getPosition().y + intersection.height});
            }
        }
    }
}

void EntityManager::update(float deltaTime, Player* player, World* world) {
    for (auto& entity : _entities) {
        if (entity.second->update(deltaTime, player, world)) {
            std::cout << "kill entity: " << entity.first << std::endl;
            killEntity(entity.first);
        }
    }

    while (!_killQueue.empty()) {
        auto id = _killQueue.front();
        _entities.erase(id);
        _killQueue.pop();
    }
    for (auto it1 = _entities.begin(); it1 != _entities.end(); ++it1) {
        if (it1->second.get()->_satisfied)
            continue;
        for (auto it2 = std::next(it1); it2 != _entities.end(); ++it2) {
            handleCollision(it1->second.get(), it2->second.get());
        }
    }
}

void EntityManager::draw() {
    for (auto& entity : _entities) {
        entity.second->draw();
    }
}
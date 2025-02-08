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
    _entities.erase(id);
}

int EntityManager::spawnEntity(Vector2 position) {
    _entities[_nextId++] = std::make_unique<Entity>();
    _entities[_nextId]->setPosition(position);
    return _nextId - 1;
}

void EntityManager::update(float deltaTime) {
    for (auto& entity : _entities) {
        entity.second->update(deltaTime);
    }
}

void EntityManager::draw() {
    for (auto& entity : _entities) {
        entity.second->draw();
    }
}
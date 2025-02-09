/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#include "GameManager.hpp"

GameManager::GameManager(World *world, EntityManager *entityManager,
                         Player *player)
    : _world(world), _entityManager(entityManager), _player(player) {
    _bonusManager = new BonusManager();
}

GameManager::~GameManager() {
    // Destructor implementation
}

void GameManager::update(float deltaTime) {
    _entityManager->update(deltaTime, _player, _world, _bonusManager);
    _world->spawnEntities(_entityManager, _bonusManager,
                          _player->getBoundingBox());
    _bonusManager->update(deltaTime, _player);
}

void GameManager::draw() {
    _bonusManager->draw();
}
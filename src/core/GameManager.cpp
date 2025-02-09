/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#include "GameManager.hpp"

GameManager::GameManager(World *world, EntityManager *entityManager,
                         Player *player)
    : _world(world), _entityManager(entityManager), _player(player) {
    // Constructor implementation
}

GameManager::~GameManager() {
    // Destructor implementation
}

void GameManager::update(float deltaTime, Vector2 camTopLeft,
                         Vector2 screenSize) {
    _spawnTimer += deltaTime;
    if (_spawnTimer > 0.5) {
        for (int i = 0; i < 4; i++) {
            std::cout << "test" << std::endl;
            _entityManager->spawnEntity(
                _world->getSpawn(camTopLeft, screenSize));
        }

        _spawnTimer = 0;
    }
}
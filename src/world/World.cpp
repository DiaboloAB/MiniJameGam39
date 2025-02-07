/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#include "World.hpp"

World::World() {
    _chunks = std::unordered_map<Vector2, Chunk>();
    // Constructor implementation
}

World::~World() {
    // Destructor implementation
}

void World::drawChunk(Vector2 position) {
    // Draw the chunk at the given position
}
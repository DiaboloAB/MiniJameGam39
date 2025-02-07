/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#include "World.hpp"
#include "raylib.h"

World::World() {
    _chunks = std::unordered_map<std::pair<int, int>, Chunk,
                                 std::hash<std::pair<int, int>>, PairEqual>();
    for (int i = -2; i < 2; i++) {
        for (int j = -2; j < 2; j++) {
            auto chunkCoords = std::make_pair(i, j);
            _chunks[chunkCoords].generate();
        }
    }
    // Constructor implementation
}

World::~World() {
    // Destructor implementation
}

void World::drawChunk(Vector2 position) {
    auto chunkCoords = std::make_pair((int)position.x, (int)position.y);

    _chunks[chunkCoords].draw(Vector2{position.x * Chunk::SIZE * 32 * 128,
                                      position.y * Chunk::SIZE * 32 * 128});
}
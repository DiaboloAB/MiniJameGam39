/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#include "World.hpp"
#include "raylib.h"

World::World() {
    // _chunks = std::unordered_map<std::pair<int, int>, Chunk,
    //                              std::hash<std::pair<int, int>>,
    //                              PairEqual>();
    // for (int i = -2; i < 2; i++) {
    //     for (int j = -2; j < 2; j++) {
    //         auto chunkCoords = std::make_pair(i, j);
    //         _chunks[chunkCoords].generate();
    //     }
    // }

    _tileset = LoadImage("assets/tilemap.png");
    _tilesetTexture = LoadTextureFromImage(_tileset);
    _tilemap = std::make_unique<Tilemap>();
    _tilemap->loadFromFile("assets/tilemap/untitled.tmx");
}

World::~World() {
    // Destructor implementation
}

void World::drawChunk(Vector2 position) {
    _tilemap->draw(_tilesetTexture);
    _tilemap->drawWall();
}

Rectangle World::getCollisions(Rectangle player) {
    return _tilemap->getCollisions(player);
}
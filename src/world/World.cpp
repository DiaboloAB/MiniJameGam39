/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#include "World.hpp"
#include "raylib.h"

// std
#include <iostream>

World::World() {
    _chunks = std::unordered_map<std::pair<int, int>, int,
                                 std::hash<std::pair<int, int>>, PairEqual>();
    for (int i = -100; i < 100; i++) {
        for (int j = -100; j < 100; j++) {
            auto chunkCoords = std::make_pair(i, j);
            _chunks[chunkCoords] = 0;
        }
    }

    _tileset = LoadImage("assets/tilemap.png");
    _tilesetTexture = LoadTextureFromImage(_tileset);
    _tilemap = std::make_unique<Tilemap>();
    _tilemap->loadFromFile("assets/tilemap/untitled.tmx");
}

World::~World() {
    // Destructor implementation
}

Vector2 World::getChunkXY(Vector2 position) {
    Vector2 chunkXY = {0, 0};

    position.x += 32 * 16 * 4 * 4;
    position.y += 32 * 16 * 4 * 4;

    chunkXY.x = (int)position.x / (32 * 16 * 4) - 4;
    chunkXY.y = (int)position.y / (32 * 16 * 4) - 4;

    return chunkXY;
}

void World::drawChunks(Vector2 camTopLeft, Vector2 screenSize, int layer) {
    int chunkSize = 32 * 16 * 4;

    Vector2 startChunk = getChunkXY(camTopLeft);
    Vector2 endChunk = getChunkXY(
        (Vector2){camTopLeft.x + screenSize.x, camTopLeft.y + screenSize.y});

    for (int i = startChunk.x; i <= endChunk.x; i++) {
        for (int j = startChunk.y; j <= endChunk.y; j++) {
            auto chunkCoords = std::make_pair(i, j);
            if (_chunks.find(chunkCoords) == _chunks.end()) {
                _chunks[chunkCoords] = 0;
            }

            Vector2 chunkPos = {i * chunkSize, j * chunkSize};
            _tilemap->drawLayer(_tilesetTexture, chunkPos, camTopLeft,
                                screenSize, layer);
        }
    }
}

Rectangle World::getCollisions(Rectangle player) {
    int chunkSize = 32 * 16 * 4;

    Vector2 startChunk = getChunkXY((Vector2){player.x, player.y});
    Vector2 endChunk = getChunkXY(
        (Vector2){player.x + player.width, player.y + player.height});

    for (int i = startChunk.x; i <= endChunk.x; i++) {
        for (int j = startChunk.y; j <= endChunk.y; j++) {
            auto chunkCoords = std::make_pair(i, j);
            if (_chunks.find(chunkCoords) == _chunks.end()) {
                _chunks[chunkCoords] = 0;
            }

            Vector2 chunkPos = {i * chunkSize, j * chunkSize};
            Rectangle collision = _tilemap->getCollisions(player, chunkPos);
            if (collision.width != 0 && collision.height != 0) {
                return collision;
            }
        }
    }
    return {0, 0, 0, 0};
}
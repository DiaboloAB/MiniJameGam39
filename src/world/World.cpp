/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#include "World.hpp"
#include "raylib.h"
#include "raymath.h"

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

    position.x += 32 * 16 * 4 * 100;
    position.y += 32 * 16 * 4 * 100;

    chunkXY.x = (int)position.x / (32 * 16 * 4) - 100;
    chunkXY.y = (int)position.y / (32 * 16 * 4) - 100;

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

Vector2 World::getSpawn(Vector2 camTopLeft, Vector2 screenSize) {
    int chunkSize = 32 * 16 * 4;

    // get a spawn on a random chunk outside the screen
    Vector2 startChunk = Vector2Subtract(getChunkXY(camTopLeft), {1, 1});
    Vector2 endChunk =
        Vector2Add(getChunkXY((Vector2){camTopLeft.x + screenSize.x,
                                        camTopLeft.y + screenSize.y}),
                   {1, 1});

    // choose 1 chunk randomly on the border of the screen

    int side = GetRandomValue(0, 3);

    Vector2 spawnChunk = {0, 0};

    switch (side) {
        case 0:  // top
            spawnChunk.x = GetRandomValue(startChunk.x, endChunk.x);
            spawnChunk.y = startChunk.y;
            break;
        case 1:  // right
            spawnChunk.x = endChunk.x;
            spawnChunk.y = GetRandomValue(startChunk.y, endChunk.y);
            break;
        case 2:  // bottom
            spawnChunk.x = GetRandomValue(startChunk.x, endChunk.x);
            spawnChunk.y = endChunk.y;
            break;
        case 3:  // left
            spawnChunk.x = startChunk.x;
            spawnChunk.y = GetRandomValue(startChunk.y, endChunk.y);
            break;
    }

    auto chunkCoords = std::make_pair(spawnChunk.x, spawnChunk.y);
    if (_chunks.find(chunkCoords) == _chunks.end()) {
        _chunks[chunkCoords] = 0;
    }

    Vector2 chunkPos = {spawnChunk.x * chunkSize, spawnChunk.y * chunkSize};

    return Vector2Add(chunkPos, _tilemap->getSpawn());
}
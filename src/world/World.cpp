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
            _chunksSpawned[chunkCoords] = 0;
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

void World::spawnEntities(EntityManager* entityManager,
                          BonusManager* bonusManager, Rectangle player) {
    int chunkSize = 32 * 16 * 4;

    Vector2 startChunk = Vector2Subtract(
        getChunkXY((Vector2){player.x, player.y}), (Vector2){1, 1});
    Vector2 endChunk =
        Vector2Add(getChunkXY((Vector2){player.x + player.width,
                                        player.y + player.height}),
                   (Vector2){1, 1});

    for (int i = startChunk.x; i <= endChunk.x; i++) {
        for (int j = startChunk.y; j <= endChunk.y; j++) {
            if (i != startChunk.x && i != endChunk.x && j != startChunk.y &&
                j != endChunk.y)
                continue;
            auto chunkCoords = std::make_pair(i, j);
            if (_chunks.find(chunkCoords) == _chunks.end()) {
                _chunks[chunkCoords] = 0;
            }
            if (!_chunksSpawned[chunkCoords]) {
                Vector2 chunkPos = {i * chunkSize, j * chunkSize};
                _tilemap->spawnEntities(chunkPos, entityManager, bonusManager);
                _chunksSpawned[chunkCoords] = 1;
            }
        }
    }
}

Vector2 World::getRandomWinPoint() {
    float distance = 1000.0f;
    Vector2 point;
    Rectangle pointRect;

    do {
        float angle = static_cast<float>(std::rand()) / RAND_MAX * 2.0f * PI;

        point.x = distance * std::cos(angle);
        point.y = distance * std::sin(angle);

        pointRect = {point.x - 10, point.y - 10, 20, 20};

    } while (checkCollisionWithExistingRectangles(pointRect));

    return point;
}

bool World::checkCollisionWithExistingRectangles(Rectangle rect) {
    Rectangle col = getCollisions(rect);
    if (col.height == 0 && col.width == 0)
        return false;
    return true;
}
/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#ifndef TILEMAP_H
#define TILEMAP_H

#include <string>
#include <vector>

#include "raylib.h"
#include "tinyxml2.h"

class BonusManager;
class EntityManager;

class Tilemap {
public:
    bool loadFromFile(const std::string& filename);
    void drawLayer(Texture2D tileset, Vector2 chunkPos, Vector2 camTopLeft,
                   Vector2 screenSize, int layer);
    void loadMap(const char* name, const char* csvData);
    void drawWall(Vector2 position = {0, 0});

    void spawnEntities(Vector2 chunkPos, EntityManager* entityManager,
                       BonusManager* bonusManager);

    Rectangle getCollisions(Rectangle player, Vector2 position = {0, 0});

private:
    int width;
    int height;
    int tileWidth;
    int tileHeight;
    std::vector<int> layer1;
    std::vector<int> layer2;
    std::vector<int> wallLayer;
    std::vector<int> spawnLayer;
    std::vector<int> bonusLayer;
};

#endif  // TILEMAP_H
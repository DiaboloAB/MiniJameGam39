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

class Tilemap {
public:
    bool loadFromFile(const std::string& filename);
    void drawLayer(Texture2D tileset, Vector2 chunkPos, Vector2 camTopLeft,
                   Vector2 screenSize, int layer);
    void loadMap(const char* name, const char* csvData);
    void drawWall(Vector2 position = {0, 0});

    Vector2 getSpawn();

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
};

#endif  // TILEMAP_H
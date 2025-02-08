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
    void draw(Texture2D tileset, Vector2 position = {0, 0});
    void draw(Texture2D tileset, Vector2 chunkPos, Vector2 camTopLeft,
              Vector2 screenSize);

    void drawWall(Vector2 position = {0, 0});

    Rectangle getCollisions(Rectangle player, Vector2 position = {0, 0});

private:
    int width;
    int height;
    int tileWidth;
    int tileHeight;
    std::vector<int> layer1;
    std::vector<int> layer2;
    std::vector<int> wallLayer;
};

#endif  // TILEMAP_H
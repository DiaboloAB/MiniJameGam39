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
    void draw(Texture2D tileset);
    void drawWall();

    Rectangle getCollisions(Rectangle player);

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
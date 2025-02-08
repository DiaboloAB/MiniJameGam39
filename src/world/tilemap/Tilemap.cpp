/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#include <iostream>
#include <sstream>

#include "Tilemap.hpp"

bool Tilemap::loadFromFile(const std::string& filename) {
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(filename.c_str()) != tinyxml2::XML_SUCCESS) {
        std::cerr << "Failed to load file: " << filename << std::endl;
        return false;
    }

    tinyxml2::XMLElement* mapElement = doc.FirstChildElement("map");
    if (!mapElement) {
        std::cerr << "No <map> element found in file: " << filename
                  << std::endl;
        return false;
    }

    mapElement->QueryIntAttribute("width", &width);
    mapElement->QueryIntAttribute("height", &height);
    mapElement->QueryIntAttribute("tilewidth", &tileWidth);
    mapElement->QueryIntAttribute("tileheight", &tileHeight);

    tinyxml2::XMLElement* layer1Element =
        mapElement->FirstChildElement("layer");
    if (!layer1Element) {
        std::cerr << "No <layer> element found in file: " << filename
                  << std::endl;
        return false;
    }

    tinyxml2::XMLElement* dataElement =
        layer1Element->FirstChildElement("data");
    if (!dataElement) {
        std::cerr << "No <data> element found in file: " << filename
                  << std::endl;
        return false;
    }

    const char* csvData = dataElement->GetText();
    if (!csvData) {
        std::cerr << "No CSV data found in <data> element in file: " << filename
                  << std::endl;
        return false;
    }

    layer1.clear();
    std::stringstream ss(csvData);
    std::string item;
    while (std::getline(ss, item, ',')) {
        layer1.push_back(std::stoi(item));
    }

    // get wall layer
    tinyxml2::XMLElement* wallLayerElement =
        mapElement->FirstChildElement("layer")->NextSiblingElement("layer");
    if (!wallLayerElement) {
        std::cerr << "No <layer> element found in file: " << filename
                  << std::endl;
        return false;
    }

    tinyxml2::XMLElement* wallDataElement =
        wallLayerElement->FirstChildElement("data");
    if (!wallDataElement) {
        std::cerr << "No <data> element found in file: " << filename
                  << std::endl;
        return false;
    }

    const char* wallCsvData = wallDataElement->GetText();
    if (!wallCsvData) {
        std::cerr << "No CSV data found in <data> element in file: " << filename
                  << std::endl;
        return false;
    }

    wallLayer.clear();
    std::stringstream wallSs(wallCsvData);
    std::string wallItem;
    while (std::getline(wallSs, wallItem, ',')) {
        wallLayer.push_back(std::stoi(wallItem));
    }

    return true;
}

void Tilemap::draw(Texture2D layer1et, Vector2 position) {
    int ratio = 4;

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            int tileIndex = layer1[y * width + x];
            if (tileIndex > 0) {
                int sourceX =
                    (tileIndex - 1) % (layer1et.width / tileWidth) * tileWidth;
                int sourceY =
                    (tileIndex - 1) / (layer1et.width / tileWidth) * tileHeight;

                Rectangle source = {sourceX, sourceY, tileWidth, tileHeight};
                Rectangle dest = {x * tileWidth * ratio, y * tileHeight * ratio,
                                  tileWidth * ratio, tileHeight * ratio};
                dest = {dest.x + position.x, dest.y + position.y, dest.width,
                        dest.height};
                DrawTexturePro(layer1et, source, dest, {0, 0}, 0, WHITE);
            }
        }
    }
}

void Tilemap::draw(Texture2D tileset, Vector2 chunkPos, Vector2 camTopLeft,
                   Vector2 screenSize) {
    int ratio = 4;

    int startX =
        std::max(0, (int)((camTopLeft.x - chunkPos.x) / (tileWidth * ratio)));
    int endX =
        std::min(width, (int)((camTopLeft.x + screenSize.x - chunkPos.x) /
                              (tileWidth * ratio)) +
                            1);
    int startY =
        std::max(0, (int)((camTopLeft.y - chunkPos.y) / (tileHeight * ratio)));
    int endY =
        std::min(height, (int)((camTopLeft.y + screenSize.y - chunkPos.y) /
                               (tileHeight * ratio)) +
                             1);

    for (int y = startY; y < endY; ++y) {
        for (int x = startX; x < endX; ++x) {
            int tileIndex = layer1[y * width + x];
            if (tileIndex > 0) {
                int tileX = (tileIndex - 1) % (tileset.width / tileWidth);
                int tileY = (tileIndex - 1) / (tileset.width / tileWidth);
                Rectangle source = {tileX * tileWidth, tileY * tileHeight,
                                    tileWidth, tileHeight};
                Rectangle dest = {chunkPos.x + x * tileWidth * ratio,
                                  chunkPos.y + y * tileHeight * ratio,
                                  tileWidth * ratio, tileHeight * ratio};
                DrawTexturePro(tileset, source, dest, {0, 0}, 0.0f, WHITE);
            }
        }
    }
}

void Tilemap::drawWall(Vector2 position) {
    int ratio = 4;
    Color color = {255, 0, 0, 255};

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            int tileIndex = wallLayer[y * width + x];
            if (tileIndex > 0) {
                int sourceY =
                    (tileIndex - 1) / (tileWidth / tileWidth) * tileHeight;

                Rectangle dest = {x * tileWidth * ratio, y * tileHeight * ratio,
                                  tileWidth * ratio, tileHeight * ratio};
                dest = {dest.x + position.x, dest.y + position.y, dest.width,
                        dest.height};
                DrawRectangleRec(dest, color);
            }
        }
    }
}

Rectangle Tilemap::getCollisions(Rectangle player, Vector2 position) {
    int ratio = 4;

    int startX =
        std::max(0, (int)((player.x - position.x) / (tileWidth * ratio)));
    int endX = std::min(width, (int)((player.x + player.width - position.x) /
                                     (tileWidth * ratio)) +
                                   1);
    int startY =
        std::max(0, (int)((player.y - position.y) / (tileHeight * ratio)));
    int endY = std::min(height, (int)((player.y + player.height - position.y) /
                                      (tileHeight * ratio)) +
                                    1);

    for (int y = startY; y < endY; ++y) {
        for (int x = startX; x < endX; ++x) {
            int tileIndex = wallLayer[y * width + x];
            if (tileIndex > 0) {
                Rectangle tileRect = {x * tileWidth * ratio,
                                      y * tileHeight * ratio, tileWidth * ratio,
                                      tileHeight * ratio};
                tileRect = {tileRect.x + position.x, tileRect.y + position.y,
                            tileRect.width, tileRect.height};
                if (CheckCollisionRecs(player, tileRect)) {
                    return tileRect;
                }
            }
        }
    }
    return {0, 0, 0, 0};
}
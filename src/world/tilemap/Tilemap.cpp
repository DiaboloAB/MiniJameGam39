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

void Tilemap::draw(Texture2D layer1et) {
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

                DrawTexturePro(layer1et, source, dest, {0, 0}, 0, WHITE);
            }
        }
    }
}

void Tilemap::drawWall() {
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

                DrawRectangleRec(dest, color);
            }
        }
    }
}

Rectangle Tilemap::getCollisions(Rectangle player) {
    int ratio = 4;

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            int tileIndex = wallLayer[y * width + x];
            if (tileIndex > 0) {
                Rectangle tile = {x * tileWidth * ratio, y * tileHeight * ratio,
                                  tileWidth * ratio, tileHeight * ratio};

                if (CheckCollisionRecs(player, tile)) {
                    Rectangle collision = GetCollisionRec(player, tile);
                    return collision;
                }
            }
        }
    }

    return {0, 0, 0, 0};
}
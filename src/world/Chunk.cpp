/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#include "Chunk.hpp"

// std
#include <iostream>

Chunk::Chunk() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            tiles[i][j] = TileType::EMPTY;
}

Chunk::~Chunk() {
    // Destructor implementation
}

TileType Chunk::getTile(int x, int y) {
    return tiles[x][y];
}

void Chunk::setTile(int x, int y, TileType type) {
    tiles[x][y] = type;
}

void Chunk::generate() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int random = rand() % 100;
            if (random < 10)
                tiles[i][j] = TileType::ROAD;
            else if (random < 20)
                tiles[i][j] = TileType::BUILDING;
            else
                tiles[i][j] = TileType::EMPTY;
        }
    }
}
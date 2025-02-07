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
        tiles[i][SIZE / 2] = TileType::ROAD;  // Horizontal road
        tiles[SIZE / 2][i] = TileType::ROAD;  // Vertical road
    }
}

void Chunk::draw(Vector2 position) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            Vector2 tilePosition = {position.x + i * TILE_SIZE,
                                    position.y + j * TILE_SIZE};
            switch (tiles[i][j]) {
                case TileType::EMPTY:
                    DrawRectangle(tilePosition.x, tilePosition.y, TILE_SIZE,
                                  TILE_SIZE, WHITE);
                    break;
                case TileType::ROAD:
                    DrawRectangle(tilePosition.x, tilePosition.y, TILE_SIZE,
                                  TILE_SIZE, RED);
                    break;
                case TileType::BUILDING:
                    DrawRectangle(tilePosition.x, tilePosition.y, TILE_SIZE,
                                  TILE_SIZE, BROWN);
                    break;
            }
        }
    }
}
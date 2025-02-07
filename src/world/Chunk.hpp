/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#ifndef CHUNK_H
#define CHUNK_H

// std
#include <iostream>
#include <vector>

enum class TileType { EMPTY, ROAD, BUILDING };

class Chunk {
public:
    Chunk();
    ~Chunk();

    static const size_t SIZE = 32;
    TileType tiles[SIZE][SIZE];

    TileType getTile(int x, int y);
    void setTile(int x, int y, TileType type);

    void generate();

private:
};

#endif  // CHUNK_H
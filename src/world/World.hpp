/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#ifndef WORLD_H
#define WORLD_H

#include "raylib.h"
#include "tinyxml2.h"
#include "world/tilemap/Tilemap.hpp"

// std
#include <memory>
#include <unordered_map>
#include <vector>

namespace std {
template <>
struct hash<std::pair<int, int>> {
    std::size_t operator()(const std::pair<int, int>& p) const noexcept {
        return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
    }
};
}  // namespace std

struct PairEqual {
    bool operator()(const std::pair<int, int>& lhs,
                    const std::pair<int, int>& rhs) const {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }
};

class World {
public:
    World();
    ~World();

    void drawChunks(Vector2 camTopLeft, Vector2 screenSize, int layer = 1);

    Rectangle getCollisions(Rectangle player);

    Vector2 getChunkXY(Vector2 position);

    Vector2 getSpawn(Vector2 camTopLeft, Vector2 screenSize);

private:
    Image _tileset;
    Texture2D _tilesetTexture;
    std::unique_ptr<Tilemap> _tilemap;

    std::unordered_map<std::pair<int, int>, int, std::hash<std::pair<int, int>>,
                       PairEqual>
        _chunks;
};

#endif  // WORLD_H
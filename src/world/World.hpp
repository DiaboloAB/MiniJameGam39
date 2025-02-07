/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#ifndef WORLD_H
#define WORLD_H

#include "Chunk.hpp"
#include "raylib.h"
#include "tinyxml2.h"

// std
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

    void drawChunk(Vector2 position);

private:
    // Image _tileset = Image();

    // // xml tilemap
    // tinyxml2::XMLDocument _doc = tinyxml2::XMLDocument();

    std::unordered_map<std::pair<int, int>, Chunk,
                       std::hash<std::pair<int, int>>, PairEqual>
        _chunks;
};

#endif  // WORLD_H
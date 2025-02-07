/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#ifndef WORLD_H
#define WORLD_H

#include "Chunk.hpp"
#include "raylib.h"

// std
#include <unordered_map>
#include <vector>

namespace std {
template <>
struct hash<Vector2> {
    std::size_t operator()(const Vector2& v) const noexcept {
        return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1);
    }
};
}  // namespace std

class World {
public:
    World();
    ~World();

    void drawChunk(Vector2 position);

private:
    std::unordered_map<Vector2, Chunk> _chunks;
};

#endif  // WORLD_H
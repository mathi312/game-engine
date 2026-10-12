#pragma once // only include header once

#include "vec2.hpp"
#include <optional>

namespace engine {

struct Rect {
    float x = 0, y = 0, w = 0, h = 0; // top-left origin, y axis goes down
    bool operator==(const Rect&) const = default;
    float right() const;
    float bottom() const;
    Vec2 center() const;
    bool contains(Vec2 p) const;
    bool overlaps(const Rect& o) const; 
    std::optional<Rect> intersection(const Rect& o) const;
    Rect expanded(float margin) const;
};

}

#include "rect.hpp"
#include <vector>

using namespace std;

namespace engine {

float Rect::right() const {
    return x + w;
}

float Rect::bottom() const {
    return y + h;
}

Vec2 Rect::center() const {
    return Vec2{(x + w) / 2, (y + h) / 2};
}

bool Rect::contains(Vec2 p) const {
    if (p.x < right() && p.x >= x && p.y < bottom() && p.y >= y) {
        return true;
    } else {
        return false;
    }
}

bool Rect::overlaps(const Rect& o) const {
    return o.x < right() && o.right() > x &&
       o.y < bottom() && o.bottom() > y;
}

std::optional<Rect> Rect::intersection(const Rect& o) const {
    const float left = std::max(x, o.x);
    const float top = std::max(y, o.y);
    const float right_ = std::min(right(), o.right());
    const float bottom_ = std::min(bottom(), o.bottom());

    if (left >= right_ || top >= bottom_) {
        return std::nullopt;
    }
    
    return Rect{left, top, right_ - left, bottom_ - top};
}

Rect Rect::expanded(float margin) const {
    return Rect{x - margin, y - margin, w + (2 * margin), h + (2 * margin)};
}

}

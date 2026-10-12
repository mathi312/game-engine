#include "test.hpp"
#include "engine/vec2.cpp"
#include "engine/rect.cpp"

using engine::Vec2;
using engine::Rect;

int main() {
    Rect a{0, 0, 10, 10}, b{5, 5, 10, 10}, c{10, 0, 5, 5};
    CHECK(a.overlaps(b));
    CHECK(!a.overlaps(c));
    auto i = a.intersection(b);
    CHECK(i.has_value() && *i == (Rect{5, 5, 5, 5}));
    CHECK(!a.intersection(c).has_value());
    CHECK(a.contains({0, 0}));
    CHECK(!a.contains({10, 10}));
    CHECK(a.expanded(1) == (Rect{-1, -1, 12, 12}));
    CHECK(a.center() == (Vec2{5, 5}));
}
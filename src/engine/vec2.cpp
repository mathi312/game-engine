#include "vec2.hpp"
#include <cmath>

namespace engine {

Vec2 Vec2::operator+(Vec2 o) const { return {x + o.x, y + o.y}; }
Vec2 Vec2::operator-(Vec2 o) const { return {x - o.x, y - o.y}; }
Vec2 Vec2::operator*(float s) const { return {x * s, y * s}; }

float Vec2::dot(Vec2 o) const { return x * o.x + y * o.y; }
float Vec2::cross(Vec2 o) const { return x * o.y - y * o.x; }

float Vec2::lengthSq() const { return x * x + y * y; }
float Vec2::length() const { return std::sqrt(lengthSq()); }

Vec2 Vec2::normalized() const {
    float len = length();
    if (len == 0.0f) return {0.0f, 0.0f};
    return {x / len, y / len};
}

Vec2 Vec2::perp() const { return {-y, x}; }

Vec2 Vec2::rotated(float radians) const {
    float c = std::cos(radians);
    float s = std::sin(radians);
    return {x * c - y * s, x * s + y * c};
}

Vec2 Vec2::lerp(Vec2 a, Vec2 b, float t) {
    return a + (b - a) * t;
}

}

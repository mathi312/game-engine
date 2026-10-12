#pragma once // only include header once

namespace engine {

struct Vec2 {
    float x = 0, y = 0;
    bool operator==(const Vec2&) const = default;
    Vec2 operator+(Vec2 o) const;
    Vec2 operator-(Vec2 o) const;
    Vec2 operator*(float s) const;
    float dot(Vec2 o) const;
    float cross(Vec2 o) const; 
    float lengthSq() const;
    float length() const;
    Vec2 normalized() const;
    Vec2 perp() const;
    Vec2 rotated(float radians) const;
    static Vec2 lerp(Vec2 a, Vec2 b, float t);
};

}

#pragma once // only include header once

#include "vec2.hpp"
#include <optional>

namespace engine {

struct Mat3 {
    float m[9];
    static Mat3 identity();
    static Mat3 translation(Vec2 t);
    static Mat3 rotation(float radians);
    static Mat3 scale(Vec2 s);
    Mat3 operator*(const Mat3& rhs) const;
    Vec2 transformPoint(Vec2 p) const;
    Vec2 transformVector(Vec2 v) const;
    std::optional<Mat3> inverse() const;
};

}

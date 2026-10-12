#include "mat3.hpp"
#include <cmath>

namespace engine {

Mat3 Mat3::identity() { return Mat3{{1, 0, 0, 0, 1, 0, 0, 0, 1}}; }
Mat3 Mat3::translation(Vec2 t) { return Mat3{{1, 0, t.x, 0, 1, t.y, 0, 0, 1}}; }

Mat3 Mat3::rotation(float radians) {
    float c = std::cos(radians);
    float s = std::sin(radians);

    return Mat3{{c, -s, 0, s, c, 0, 0, 0, 1}};
}

Mat3 Mat3::scale(Vec2 s) { return Mat3{{s.x, 0, 0, 0, s.y, 0, 0, 0, 1}}; }

Mat3 Mat3::operator*(const Mat3& rhs) const {
    float c11 = m[0] * rhs.m[0] + m[1] * rhs.m[3] + m[2] * rhs.m[6];
    float c12 = m[0] * rhs.m[1] + m[1] * rhs.m[4] + m[2] * rhs.m[7];
    float c13 = m[0] * rhs.m[2] + m[1] * rhs.m[5] + m[2] * rhs.m[8];
    float c21 = m[3] * rhs.m[0] + m[4] * rhs.m[3] + m[5] * rhs.m[6];
    float c22 = m[3] * rhs.m[1] + m[4] * rhs.m[4] + m[5] * rhs.m[7];
    float c23 = m[3] * rhs.m[2] + m[4] * rhs.m[5] + m[5] * rhs.m[8];
    float c31 = m[6] * rhs.m[0] + m[7] * rhs.m[3] + m[8] * rhs.m[6];
    float c32 = m[6] * rhs.m[1] + m[7] * rhs.m[4] + m[8] * rhs.m[7];
    float c33 = m[6] * rhs.m[2] + m[7] * rhs.m[5] + m[8] * rhs.m[8];

    return Mat3{{c11, c12, c13, c21, c22, c23, c31, c32, c33}};
}

Vec2 Mat3::transformPoint(Vec2 p) const {
    float x = m[0] * p.x + m[1] * p.y + m[2] * 1;
    float y = m[3] * p.x + m[4] * p.y + m[5] * 1;

    return Vec2{x, y};
}

Vec2 Mat3::transformVector(Vec2 v) const {
    float x = m[0] * v.x + m[1] * v.y;
    float y = m[3] * v.x + m[4] * v.y;

    return Vec2{x, y};
}

std::optional<Mat3> Mat3::inverse() const {
    // det = a * d - b * c.
    float det = m[0] * m[4] - m[1] * m[3];

    if (std::fabs(det) < 1e-8f) {
        return std::nullopt;
    }

    float ia = m[4] / det;
    float ib = (-m[1]) / det;
    float ic = (-m[3]) /det;
    float id = m[0] /det;

    float itx = -(ia * m[2] + ib * m[5]);
    float ity = -(ic * m[2] + id * m[5]);

    return Mat3{{ia, ib, itx, ic, id, ity, 0, 0, 1}};
}

}

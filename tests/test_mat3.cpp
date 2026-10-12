#include "test.hpp"
#include "engine/vec2.cpp"
#include "engine/mat3.cpp"

using engine::Vec2;
using engine::Mat3;

int main() {
    const float pi = 3.14159265f;
    Vec2 p = Mat3::translation({10, 5}).transformPoint({1, 1});
    CHECK_NEAR(p.x, 11); CHECK_NEAR(p.y, 6);
    Vec2 v = Mat3::translation({10, 5}).transformVector({1, 1});
    CHECK_NEAR(v.x, 1); CHECK_NEAR(v.y, 1);
    Mat3 m = Mat3::translation({10, 0}) * Mat3::rotation(pi / 2);   // rotate, then translate
    p = m.transformPoint({1, 0});
    CHECK_NEAR(p.x, 10); CHECK_NEAR(p.y, 1);
    p = Mat3::scale({2, 3}).transformPoint({1, 1});
    CHECK_NEAR(p.x, 2); CHECK_NEAR(p.y, 3);
    Mat3 full = Mat3::translation({3, 4}) * Mat3::rotation(0.7f) * Mat3::scale({2, 2});
    auto inv = full.inverse();
    CHECK(inv.has_value());
    p = ((*inv) * full).transformPoint({5, -2});
    CHECK_NEAR(p.x, 5); CHECK_NEAR(p.y, -2);
    CHECK(!Mat3::scale({0, 1}).inverse().has_value());
}

#include "test.hpp"
#include "engine/vec2.cpp"

using engine::Vec2;

int main() {
    const float pi = 3.14159265f;
    CHECK((Vec2{1, 2} + Vec2{3, 4}) == (Vec2{4, 6}));
    CHECK((Vec2{1, 2} * 2.f) == (Vec2{2, 4}));
    CHECK_NEAR((Vec2{3, 4}).length(), 5.0);
    CHECK_NEAR((Vec2{3, 4}).normalized().length(), 1.0);
    CHECK((Vec2{0, 0}).normalized() == (Vec2{0, 0}));
    CHECK_NEAR((Vec2{1, 0}).dot(Vec2{0, 1}), 0.0);
    CHECK_NEAR((Vec2{1, 0}).cross(Vec2{0, 1}), 1.0);
    Vec2 r = (Vec2{1, 0}).rotated(pi / 2);
    CHECK_NEAR(r.x, 0.0); CHECK_NEAR(r.y, 1.0);
    CHECK((Vec2::lerp({0, 0}, {10, 20}, 0.5f)) == (Vec2{5, 10}));
    TEST_MAIN_END();
}

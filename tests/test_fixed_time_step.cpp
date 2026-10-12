#include "test.hpp"
#include "engine/fixed_time_step.cpp"

using engine::FixedTimestep;

int main() {
    FixedTimestep ft(1.0 / 60);
    CHECK(ft.advance(1.0 / 60) == 1);
    CHECK(ft.advance(0.5 / 60) == 0);
    CHECK_NEAR(ft.alpha(), 0.5);
    CHECK(ft.advance(0.5 / 60) == 1);
    FixedTimestep slow(1.0 / 60, 0.25);
    int n = slow.advance(10.0);
    CHECK(n >= 14 && n <= 15);
    FixedTimestep ft2(0.01);
    CHECK(ft2.advance(0.035) == 3);
    CHECK_NEAR(ft2.alpha(), 0.5);
}

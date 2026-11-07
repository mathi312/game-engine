#include "test.hpp"
#include "engine/input_state.cpp"

using engine::InputState;
using engine::Key;

int main() {
    InputState in;
    in.beginFrame();
    in.setKey(Key::Space, true);
    CHECK(in.down(Key::Space) && in.pressed(Key::Space) && !in.released(Key::Space));
    in.beginFrame();
    CHECK(in.down(Key::Space) && !in.pressed(Key::Space));
    in.setKey(Key::Space, true);                  // key repeat
    CHECK(!in.pressed(Key::Space));
    in.beginFrame();
    in.setKey(Key::Space, false);
    CHECK(!in.down(Key::Space) && in.released(Key::Space));
    in.beginFrame();
    CHECK(!in.released(Key::Space));
    in.setKey(Key::Right, true);
    CHECK_NEAR(in.axis(Key::Left, Key::Right), 1.0);
    in.setKey(Key::Left, true);
    CHECK_NEAR(in.axis(Key::Left, Key::Right), 0.0);
}

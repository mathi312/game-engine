#include "input_state.hpp"
#include <cstddef>

namespace engine {

void InputState::beginFrame() {
    previous = std::move(current);
}

void InputState::setKey(Key k, bool isDown) {
    current[index(k)] = isDown;
}

bool InputState::down(Key k) const {
    return current[index(k)];
}

bool InputState::pressed(Key k) const {
    return current[index(k)] && !previous[index(k)];
}

bool InputState::released(Key k) const {
    return !current[index(k)] && previous[index(k)];
}

float InputState::axis(Key negative, Key positive) const {
    float neg = down(negative) ? 1.0f : 0.0f;
    float pos = down(positive) ? 1.0f : 0.0f;
    return pos - neg;
}

} // namespace engine

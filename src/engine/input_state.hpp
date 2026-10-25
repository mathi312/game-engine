#pragma once
#include <array>
#include <cassert>
#include <cstdint>

namespace engine {

enum class Key { Left, Right, Up, Down, Space, Escape, Count };

class InputState {
private:
    static constexpr std::size_t N = static_cast<std::size_t>(Key::Count);

    static constexpr std::size_t index(Key k) {
        assert(k != Key::Count);
        return static_cast<std::size_t>(k);
    }

    std::array<bool, N> current{};
    std::array<bool, N> previous{};
public:
    void beginFrame();
    void setKey(Key k, bool isDown);
    bool down(Key k) const;
    bool pressed(Key k) const;
    bool released(Key k) const;
    float axis(Key negative, Key positive) const;
};

} // namespace engine

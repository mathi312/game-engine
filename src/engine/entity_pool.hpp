#pragma once // only include header once
#include <cstdint>

namespace engine {

struct Entity {
    uint32_t index = 0, generation = 0;
    bool operator==(const Entity&) const = default;
};

class EntityPool {
public:
    Entity create();
    void destroy(Entity e);
    bool alive(Entity e) const;
    size_t aliveCount() const;
    Entity handleFor(uint32_t index) const;
};

}

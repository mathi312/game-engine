#pragma once // only include header once
#include <cstdint>
#include <vector>
#include <deque>

namespace engine {

struct Entity {
    uint32_t index = 0, generation = 0;
    bool isAlive = true;
    bool operator==(const Entity&) const = default;
};

class EntityPool {
private:
    std::vector<Entity> entities;
    std::deque<uint32_t> freeList;

public:
    Entity create();
    void destroy(Entity e);
    bool alive(Entity e) const;
    size_t aliveCount() const;
    Entity handleFor(uint32_t index) const;
};

} // namespace engine

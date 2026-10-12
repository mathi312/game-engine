#include "entity_pool.hpp"
#include <cassert>

namespace engine {

Entity EntityPool::create() {
    uint32_t targetIndex;
    Entity entity;

    if (freeList.empty()) {
        targetIndex = static_cast<uint32_t>(entities.size());
        entity = Entity{targetIndex, 0};
        entities.push_back(entity);
    } else {
        targetIndex = freeList.back();
        freeList.pop_back();

        entity = Entity{targetIndex, entities[targetIndex].generation + 1};

        entities[targetIndex] = entity;
    }

    return entity;
}

void EntityPool::destroy(Entity e) {
    if (e.index < entities.size() && entities[e.index] == e) {
        entities[e.index].isAlive = false;
        freeList.push_front(e.index);
    }
}

bool EntityPool::alive(Entity e) const {
    return e.index < entities.size()
        && entities[e.index].generation == e.generation
        && entities[e.index].isAlive;
}

size_t EntityPool::aliveCount() const {
    return entities.size() - freeList.size();
}

Entity EntityPool::handleFor(uint32_t index) const {
    assert(index < entities.size());
    return entities[index];
}

} // namespace
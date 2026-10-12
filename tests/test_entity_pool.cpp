#include "test.hpp"
#include "engine/entity_pool.cpp"

using engine::EntityPool;
using engine::Entity;

int main() {
    EntityPool p;
    Entity a = p.create(), b = p.create();
    CHECK(a != b);
    CHECK(p.alive(a));
    p.destroy(a);
    CHECK(!p.alive(a));
    Entity c = p.create();
    CHECK(c.index == a.index);
    CHECK(c.generation == a.generation + 1);
    CHECK(!p.alive(a));
    CHECK(p.alive(c));
    p.destroy(a);
    CHECK(p.alive(c));
    CHECK(p.aliveCount() == 2);
}

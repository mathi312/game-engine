#include "test.hpp"
#include "engine/sparse_set.hpp"

using engine::SparseSet;

int main() {
    SparseSet<int> s;
    s.insert(5, 50); s.insert(9, 90); s.insert(100000, 7);
    CHECK(s.size() == 3);
    CHECK(*s.get(9) == 90);
    CHECK(s.erase(9));
    CHECK(!s.erase(9));
    CHECK(!s.contains(9));
    CHECK(s.get(9) == nullptr);
    CHECK(*s.get(5) == 50 && *s.get(100000) == 7);
    CHECK(s.values().size() == 2);
    s.insert(5, 51);
    CHECK(*s.get(5) == 51);
    CHECK(s.size() == 2);
}

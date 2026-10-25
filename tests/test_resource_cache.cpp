#include "test.hpp"
#include "engine/resource_cache.hpp"

using engine::ResourceCache;

int main() {
    int loads = 0;
    ResourceCache<std::string> cache([&](const std::string& path) -> std::shared_ptr<std::string> {
        ++loads;
        if (path == "missing") return nullptr;
        return std::make_shared<std::string>(path + "!");
    });
    auto a = cache.get("hero.png");
    auto b = cache.get("hero.png");
    CHECK(a == b && loads == 1 && *a == "hero.png!");
    CHECK(cache.get("missing") == nullptr);
    CHECK(cache.cachedCount() == 1);
    a.reset(); b.reset();
    cache.collectGarbage();
    CHECK(cache.cachedCount() == 0);
    auto c = cache.get("hero.png");
    CHECK(loads == 3);
}

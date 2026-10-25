#pragma once
#include <cstddef>
#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <utility>

namespace engine {

template <class T>
class ResourceCache {
public:
    using Loader = std::function<std::shared_ptr<T>(const std::string& path)>;

    explicit ResourceCache(Loader loader)
        : loader(std::move(loader)) {}

    std::shared_ptr<T> get(const std::string& path) {
        if (cache.contains(path) && !cache.find(path)->second.expired()) {
            return cache.find(path)->second.lock();
        }
        
        // Load the resource and cache it
        std::shared_ptr<T> resource = loader(path);

        if (!resource) {
            return nullptr;
        }

        std::weak_ptr<T> weakResource = resource;
        cache.emplace(path, weakResource);

        return resource;
    }

    size_t cachedCount() const {
        std::size_t count = 0;

        for (const auto& [path, weakResource] : cache) {
            if (!weakResource.expired()) {
                ++count;
            }
        }

        return count;
    }

    void collectGarbage() {
        for (auto it = cache.begin(); it != cache.end();) {
            if (it->second.expired()) {
                it = cache.erase(it);
            } else {
                ++it;
            }
        }
    }

private:
    Loader loader;
    std::unordered_map<std::string, std::weak_ptr<T>> cache;
};

} // namespace engine

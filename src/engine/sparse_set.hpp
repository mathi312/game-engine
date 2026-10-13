#pragma once
#include <cstddef>
#include <cstdint>
#include <span>
#include <utility>
#include <vector>

namespace engine {

template <class T>
class SparseSet {
private:
    std::vector<uint32_t> sparse; // id -> index in dense
    std::vector<uint32_t> denseIds; // index -> id
    std::vector<T> dense; // index -> value

public:
    T& insert(uint32_t id, T value) {
        if (contains(id)) {
            dense[sparse[id]] = std::move(value);
            return dense[sparse[id]];
        }
        if (id >= sparse.size()) sparse.resize(id + 1);
        sparse[id] = static_cast<uint32_t>(dense.size());
        denseIds.push_back(id);
        dense.push_back(std::move(value));
        return dense.back();
    }

    bool erase(uint32_t id) {
        if (!contains(id)) return false;

        const uint32_t index = sparse[id];
        const uint32_t last = static_cast<uint32_t>(dense.size() - 1);

        if (index != last) {                      // swap-and-pop
            const uint32_t lastId = denseIds[last];
            dense[index] = std::move(dense[last]);
            denseIds[index] = lastId;
            sparse[lastId] = index;
        }
        dense.pop_back();
        denseIds.pop_back();
        return true;
    }

    bool contains(uint32_t id) const {
        return id < sparse.size()
            && sparse[id] < denseIds.size()
            && denseIds[sparse[id]] == id;
    }

    T* get(uint32_t id) {
        return contains(id) ? &dense[sparse[id]] : nullptr;
    }

    const T* get(uint32_t id) const {
        return contains(id) ? &dense[sparse[id]] : nullptr;
    }

    size_t size() const { return dense.size(); }

    std::span<T> values() { return dense; }
    std::span<const T> values() const { return dense; }
    std::span<const uint32_t> ids() const { return denseIds; }
};

} // namespace engine

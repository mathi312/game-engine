#pragma once 
#include <cstdint>
#include <functional>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <typeindex>

namespace engine {

using ConnectionId = uint32_t;


struct Handler {
    ConnectionId id;
    std::function<void(const void*)> fn;

    template <class E> Handler(ConnectionId id, std::function<void(const E&)> fn) : id(id) {
        this->fn = [fn](const void* e) {
            fn(*static_cast<const E*>(e));
        };
    }
};

class EventBus {
private:
    ConnectionId unique_id = 0;
    std::unordered_map<std::type_index, std::vector<Handler>> event_bus;
    std::unordered_map<ConnectionId, std::type_index> id_to_index;
    std::vector<std::function<void()>> event_queue;
    bool is_flushing = false;
public:
    template <class E> ConnectionId subscribe(std::function<void(const E&)> fn) {
        ConnectionId id = unique_id;
        unique_id++;

        Handler h = Handler{id, std::move(fn)};

        event_bus[std::type_index(typeid(E))].push_back(std::move(h));
        id_to_index.emplace(id, std::type_index(typeid(E)));

        return id;
    }

    void unsubscribe(ConnectionId id) {
        if (!id_to_index.contains(id)) return;

        std::type_index type = id_to_index.find(id)->second;

        if (event_bus.contains(type)) {
            auto& handlers = event_bus[type];
            handlers.erase(std::remove_if(handlers.begin(), handlers.end(), [id](const Handler& handler)
            {
                return handler.id == id;
            }), handlers.end());
        }

        id_to_index.erase(id);
    }

    template <class E> void emit(const E& e) {
        if (event_bus.contains(std::type_index(typeid(E)))) {
            auto snapshot = event_bus[std::type_index(typeid(E))];

            for (const auto& handler : snapshot) {
                handler.fn(&e);
            }
        }
    }

    template <class E> void enqueue(E e) {
        event_queue.push_back([this, e = std::move(e)]() { emit(e); });
    }

    void flush() {
        if (is_flushing) return;
        is_flushing = true;

        struct Reset {
            bool& flag;
            ~Reset() { flag = false; }
        } reset{is_flushing};

        auto queue = std::move(event_queue);
        event_queue.clear();

        for (const auto& event : queue) {
            event();
        }
    }
};

} // namespace engine

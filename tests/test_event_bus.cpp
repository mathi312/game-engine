#include "test.hpp"
#include "engine/event_bus.hpp"

using engine::EventBus;
using engine::ConnectionId;

int main() {
    struct Hit { int dmg; };
    struct Jump {};
    struct Ping {};
    struct Pong {};
    EventBus bus;
    int total = 0, jumps = 0, pongs = 0;
    auto id = bus.subscribe<Hit>([&](const Hit& h) { total += h.dmg; });
    bus.subscribe<Jump>([&](const Jump&) { ++jumps; });
    bus.emit(Hit{3}); bus.emit(Jump{});
    CHECK(total == 3 && jumps == 1);
    bus.enqueue(Hit{4});
    CHECK(total == 3);
    bus.flush();
    CHECK(total == 7);
    bus.unsubscribe(id);
    bus.emit(Hit{100});
    CHECK(total == 7);
    ConnectionId self = 0;
    int calls = 0;
    self = bus.subscribe<Jump>([&](const Jump&) { ++calls; bus.unsubscribe(self); });
    bus.emit(Jump{}); bus.emit(Jump{});
    CHECK(calls == 1);
    bus.subscribe<Ping>([&](const Ping&) { bus.enqueue(Pong{}); });
    bus.subscribe<Pong>([&](const Pong&) { ++pongs; });
    bus.enqueue(Ping{});
    bus.flush();
    CHECK(pongs == 0);
    bus.flush();
    CHECK(pongs == 1);
}

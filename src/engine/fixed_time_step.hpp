#pragma once // only include header once

namespace engine {

class FixedTimestep {
private:
    double fixed_dt, acc, maxFrame;
public:
    explicit FixedTimestep(double dt, double maxFrame = 0.25);
    int advance(double frameSeconds);
    double alpha() const;
};

}

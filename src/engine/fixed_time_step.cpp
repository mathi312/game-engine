#include "fixed_time_step.hpp"
#include <algorithm>

using namespace std;

namespace engine {

FixedTimestep::FixedTimestep(double dt, double maxFrame)
    : fixed_dt(dt), maxFrame(maxFrame) {}

int FixedTimestep::advance(double frameSeconds) {
    double clampedFrame = std::clamp(frameSeconds, 0.0, maxFrame);

    acc += clampedFrame;
    int stepsToRun = 0;
    
    while (acc >= fixed_dt) {
        stepsToRun++;
        acc -= fixed_dt;
    }

    return stepsToRun;
}

double FixedTimestep::alpha() const {
    return acc;
}

}
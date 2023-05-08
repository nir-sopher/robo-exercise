#include "brain/motors_loop.h"

namespace brain
{

    MotorsLoop::MotorsLoop(const ::infra::State &aMotorsInitialState, int64_t aPeriodUs) : ::infra::StatefulLoop(aPeriodUs)
    {
        initDelayWarningThreshold(aPeriodUs / 10);
        initState(aMotorsInitialState);
    }

    bool MotorsLoop::step(infra::State *aStateP)
    {
        for (auto &motor : *aStateP)
        {
            motor.second *= (1 + 0.1);
        }
        return true;
    }
} // namespace
#include "brain/position_loop.h"

namespace brain
{

    PositionLoop::PositionLoop(const ::infra::State &aInitialPosState, int64_t aPeriodUs) : ::infra::StatefulLoop(aPeriodUs), myNoiseDistribution(MIN_NOISE_LEVEL, MAX_NOISE_LEVEL)
    {
        initDelayWarningThreshold(aPeriodUs / 10);
        initState(aInitialPosState);
    }

    bool PositionLoop::step(infra::State *aStateP)
    {
        auto found = aStateP->find(POS_KEY);
        if (found == aStateP->end())
        {
            // TODO LOG
            myStats.inc("no-pos-set", 1);
            return false;
        }

        found->second *= (1 + 0.001 * myNoiseDistribution(myRandomEngine));
        return true;
    }
} // namespace
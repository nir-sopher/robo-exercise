#pragma once
#include "infra/stateful_loop.h"

namespace brain
{
    class MotorsLoop : public ::infra::StatefulLoop
    {
    public:
        MotorsLoop(const ::infra::State &aMotorsInitialState, int64_t aPeriodUs = 10000);

    protected:
        virtual bool step(infra::State *aStateP) final;
    };
} // namespace
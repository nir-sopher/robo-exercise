
#pragma once

#include <shared_mutex>
#include "loop.h"
#include "state.h"
#include "int_stats.h"

namespace infra
{

    // A iterative work executater.
    // Periodically running a step function implemented at the derived class, manipulating the state
    class StatefulLoop : public Loop
    {
    public:
        /**
         * INITIALZATION Functions
         */
        StatefulLoop(int64_t aPeriodUs) : Loop(aPeriodUs)
        {
        }

        // Override the current state
        void overrideState(const State &aState);

        // return the current state
        State getState() const;

    protected:
        // init the managed state
        void initState(const State &aState);

        // emit a warning in cases of a delay in a call to step
        void initLockDelayWarningThreshold(int64_t aLockDelayPeriodUs)
        {
            myLockDelayPeriodUs = aLockDelayPeriodUs;
        }

        virtual bool step() final;

        // manipulate the state, implented by the derived class
        virtual bool step(State *aStateP) = 0;

    private:
        // operational
        State myState;
        mutable std::shared_timed_mutex myStateLock;
        int64_t myLockDelayPeriodUs = 0;
    };

} // namespace
#include <chrono>
#include "infra/stateful_loop.h"

namespace infra
{

    bool StatefulLoop::step()
    {
        // redirect to the step that gets the status
        auto callTime = std::chrono::high_resolution_clock::now();
        std::lock_guard<std::shared_timed_mutex> writerLock(myStateLock);
        auto lockTime = std::chrono::high_resolution_clock::now();

        if (myLockDelayPeriodUs > 0 &&
            lockTime - callTime >= std::chrono::microseconds(myLockDelayPeriodUs))
        {
            // TODO ERROR
            myStats.inc("step-delayed-due-to-lock", 1);
        }

        return step(&myState);
    }

    void StatefulLoop::initState(const State &aState)
    {
        myState = aState;
    }

    State StatefulLoop::getState() const
    {
        std::shared_lock<std::shared_timed_mutex> readerLock(myStateLock);
        State toReturn(myState);
        return toReturn;
    }

    void StatefulLoop::overrideState(const State &aState)
    {
        std::lock_guard<std::shared_timed_mutex> writerLock(myStateLock);
        myState = aState;
    }
} // namespace
#include <chrono>
#include "infra/loop.h"

namespace infra
{

    void Loop::initPersistOnOverdueSteps()
    {
        myPersistOnOverdueSteps = true;
    }

    void Loop::initDelayWarningThreshold(int64_t aDelayPeriodUs)
    {
        myDelayPeriodWarningUs = aDelayPeriodUs;
    }

    bool Loop::launch()
    {
        if (myStatus != DOWN)
        {
            // TODO LOG ERROR
            return false;
        }
        myRunningThreadP.reset(new std::thread(Loop::s_onLaunch, this));
        return true;
    }

    void Loop::terminate()
    {
        myMarkForTerminationFlag = true;
    }

    bool Loop::waitToTerminate() const
    {
        if (!myRunningThreadP)
        {
            // TODO LOG not launched
            return false;
        }
        myRunningThreadP->join();
        return true;
    }

    Loop::Status Loop::getStatus() const
    {
        return myStatus;
    }

    void Loop::loop()
    {
        myStatus = RUNNING;
        myCurentCycle = 0; // the first cycle
        auto launchTime = std::chrono::high_resolution_clock::now();
        while (!myMarkForTerminationFlag)
        {
            myStats.inc("cycle", 1);

            // calculating when the ctep should be done
            std::chrono::microseconds timeslotForThisCycle(myCurentCycle * myPeriodUs);
            auto timeOfThisCycle = launchTime + timeslotForThisCycle;

            // sleeping if needed - the amount of time needed for the timeslot,
            // avoiding the accomolation of delays
            auto now = std::chrono::high_resolution_clock::now();
            bool slept = false;
            if (now < timeOfThisCycle)
            {
                std::this_thread::sleep_for(timeOfThisCycle - now);
                myStats.inc("sleep-needed", 1);
            }

            // OK. Time to run
            // checking if we are in a delay
            now = std::chrono::high_resolution_clock::now();
            if (myDelayPeriodWarningUs > 0 &&
                timeOfThisCycle + std::chrono::microseconds(myDelayPeriodWarningUs) <= now)
            {
                // TODO WARNING
                if (slept)
                {
                    // issue number 1 - system is loaded. Sleep takes time...
                    myStats.inc("step-delayed-due-to-sleep", 1);
                }
                else
                {
                    // issue number 2 - to much work is done in each step
                    myStats.inc("step-delayed-due-to-work", 1);
                }
            }

            // was the delay so large that we had actually missed some cycles?
            if (!myPersistOnOverdueSteps)
            {
                // TODO align cycle count
                // myCurentCycle = floor((now - launchTime)/myPeriodUs);
            }

            // doing the actual step
            bool success = step();
            if (!success)
            {
                // TODO ERROR
                myStats.inc("failed-steps", 1);
                myStatus = STEP_FAILED;
                break;
            }

            myCurentCycle++;
        }

        if (myStatus == RUNNING)
        {
            myStatus = DONE;
        }
    }
} // namespace
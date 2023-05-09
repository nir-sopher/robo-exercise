#pragma once

#include <thread>
#include "int_stats.h"

namespace infra
{
    // A iterative work executater.
    // Periodically running a step function implemented at the derived class
    class Loop
    {
    public:
        enum Status
        {
            DOWN = 0,
            RUNNING,
            DONE,
            STEP_FAILED,
            INFRA_FAILED

        };

        /**
         * INITIALZATION Functions
         */
        Loop(int64_t aPeriodUs) : myPeriodUs(aPeriodUs)
        {
        }

        /*
         * MAIN USAGE Functions
         */
        // launcing the funciton periodic steps
        // return true for success
        bool launch();

        // mark the periodic steps to be terminated
        void terminate();

        // return only iterate work is done
        // return true for success
        bool waitToTerminate() const;

        // return the status of the current run
        Status getStatus() const;

        // return the loop stats.
        // unsafe - not thread safe
        IntStats getStatsUnsafe() const {
            return myStats;
        }

    protected:
        // init behavior - set the behavior in cases a delay causes multiple cycles to be missed.
        // when NOT called - the extra steps are discarded.
        void initPersistOnOverdueSteps();

        // emit a warning in cases of a delay in a call to step
        void initDelayWarningThreshold(int64_t aDelayPeriodUs);

        // do the step, implented by the derived class
        virtual bool step() = 0;

        IntStats myStats;

    private:
        // settings
        int64_t myPeriodUs;
        bool myPersistOnOverdueSteps = false;
        int64_t myDelayPeriodWarningUs = 0;

        // operational
        volatile Status myStatus = DOWN;
        std::unique_ptr<std::thread> myRunningThreadP;
        volatile bool myMarkForTerminationFlag = false;
        int64_t myCurentCycle = 0;

        // impelemtation functions
        // running the main loop of the stepper
        void loop();

        // TODO find a mor elegant way to do it
        static void s_onLaunch(Loop *aStepperP)
        {
            aStepperP->loop();
        }
    };
    
} // namespace
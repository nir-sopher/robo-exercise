#pragma once

#include <memory>

#include "infra/int_stats.h"
#include "infra/net_function.h"
#include "position_loop.h"
#include "motors_loop.h"

namespace brain
{
    class MainLoop : public ::infra::Loop
    {
    public:
        MainLoop(const std::shared_ptr<MotorsLoop> &aMotorsLoopP, const std::shared_ptr<PositionLoop> &aPositionLoopP,
                 const std::shared_ptr<::infra::NetFunction> &aNetFunctionP, int64_t aPeriodUs = 100000);

        // init to print each cycle to the provided stream.
        // Note: ptr ownership is in the user responsibility
        void initPeriodicPrint(std::ostream *aStreamP);

        // modify the print frequency (default is 1, i.e. every cycle)
        void setPeriodicPrintFreq(int64_t aCycleCount);

    protected:
        virtual bool step() final;

    private:
        std::shared_ptr<MotorsLoop> myMotorLoopP;
        std::shared_ptr<PositionLoop> myPositionLoopP;
        std::shared_ptr<::infra::NetFunction> myNetFunctionP;

        int64_t myStepsCount = 0;

        std::ostream *myPeriodicPrintStreamP = NULL;
        int64_t myPeriodingPrintCycleCount = 1;
    };
} // namespace
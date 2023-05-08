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

    protected:
        virtual bool step() final;

    private:
        std::shared_ptr<MotorsLoop> myMotorLoopP;
        std::shared_ptr<PositionLoop> myPositionLoopP;
        std::shared_ptr<::infra::NetFunction> myNetFunctionP;
    };
} // namespace
#include "brain/net_function_mul.h"
#include "brain/position_loop.h"

namespace brain
{

    bool NetFunctionMul::operator()(const ::infra::State &aMotorsState,
                                    const ::infra::State &aPositionState,
                                    ::infra::State *aOutputMotorsStateP)
    {
        auto positionPosStateFound = aPositionState.find(PositionLoop::POS_KEY);
        if (positionPosStateFound == aPositionState.end())
        {
            return false;
        }
        for (auto motorState : aMotorsState)
        {
            (*aOutputMotorsStateP)[motorState.first] = motorState.second * positionPosStateFound->second;
        }

        return true;
    }
} // namespace
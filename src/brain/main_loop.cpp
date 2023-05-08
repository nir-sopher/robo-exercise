#include "brain/main_loop.h"

#include <iostream>

namespace brain
{

    MainLoop::MainLoop(const std::shared_ptr<MotorsLoop> &aMotorsLoopP,
                       const std::shared_ptr<PositionLoop> &aPositionLoopP,
                       const std::shared_ptr<::infra::NetFunction> &aNetFunctionP,
                       int64_t aPeriodUs) : Loop(aPeriodUs),
                                            myMotorLoopP(aMotorsLoopP),
                                            myPositionLoopP(aPositionLoopP),
                                            myNetFunctionP(aNetFunctionP)
    {
        initDelayWarningThreshold(aPeriodUs / 10);
    }

    bool MainLoop::step()
    {
        ::infra::State motorsState = myMotorLoopP->getState();
        ::infra::State positionState = myPositionLoopP->getState();
        ::infra::State newMotorsState;
        bool success = (*myNetFunctionP)(motorsState, positionState, &newMotorsState);
        if (!success)
        {
            // TODO log
            return false;
        }

        if (myPrintEachNSteps > 0 and myStepsCount % myPrintEachNSteps == 0)
        {
            std::cout << "Round " << myStepsCount << "\n";
            std::cout << "Position: \n";
            for (auto posState : positionState)
            {
                std::cout << posState.first<<":"<<posState.second<<", ";
            }
            std::cout << "\nMotors Position: \n";
            for (auto motor : motorsState)
            {
                std::cout << motor.first<<":"<<motor.second<<", ";
            } 
            std::cout << "\nNet Result: \n";
            for (auto motor : newMotorsState)
            {
                std::cout << motor.first<<":"<<motor.second<<", ";
            }
            std::cout << "\n" << std::endl;
        }

        // careful here.
        // it might be that in the meanwhile motorsLoop proceed and did an additional step
        // As long as a gauge like behavior for the position is OK,
        // I assume it does not matter as we will just overraun the new value
        myMotorLoopP->overrideState(newMotorsState);
        myStepsCount++;
        return true;
    }

} // namespace
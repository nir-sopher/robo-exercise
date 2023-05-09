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

    void MainLoop::initPeriodicPrint(std::ostream *aStreamP)
    {
        myPeriodicPrintStreamP = aStreamP;
    }

    void MainLoop::setPeriodicPrintFreq(int64_t aCycleCount)
    {
        myPeriodingPrintCycleCount = aCycleCount;
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

        if (myPeriodicPrintStreamP != NULL &&
            myPeriodingPrintCycleCount > 0 && myStepsCount % myPeriodingPrintCycleCount == 0)
        {
            (*myPeriodicPrintStreamP) << "Round " << myStepsCount << "\n";
            (*myPeriodicPrintStreamP) << "Position: \n";
            (*myPeriodicPrintStreamP) << positionState << "\n";
            (*myPeriodicPrintStreamP) << "Motors Position: \n";
            (*myPeriodicPrintStreamP) << motorsState << "\n";
            (*myPeriodicPrintStreamP) << "Net Result: \n";
            (*myPeriodicPrintStreamP) << newMotorsState << "\n";
            (*myPeriodicPrintStreamP) << std::endl;
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
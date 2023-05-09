#include <iostream>

#include "brain/brain.h"
#include "brain/net_function_mul.h"
#include "brain/net_function_identity.h"

namespace brain
{

    infra::State myInitialPosState;
    infra::State myMotorsInitialState;
    std::shared_ptr<infra::NetFunction> myNetFunctionP;

    bool Brain::initPosition(double aInitialPosition)
    {
        if (myInitDone)
        {
            // TODO ERROR init done
            return false;
        }
        myInitialPosState[brain::PositionLoop::POS_KEY] = aInitialPosition;
        return true;
    }

    bool Brain::initAddMotor(const std::string &aMotorId, double aInitialPosition)
    {
        if (myInitDone)
        {
            // TODO ERROR init done
            return false;
        }
        myMotorsInitialState[aMotorId] = aInitialPosition;
        return true;
    }

    bool Brain::initNetFunction(const std::string &aNetFunctionType)
    {
        if (myInitDone)
        {
            // TODO ERROR init done
            return false;
        }
        myNetFunctionP.reset(infra::NetFunction::s_getByTypeUnsafe(aNetFunctionType));
        if (myNetFunctionP.get() == NULL)
        {
            // TODO ERROR - no such type
            return false;
        }
        return true;
    }

    bool Brain::initPrintEachNSteps(int64_t aN)
    {
        if (myInitDone)
        {
            // TODO ERROR init done
            return false;
        }
        myPrintEachNSteps = aN;
        return true;
    }

    bool Brain::initDone()
    {
        if (myInitDone)
        {
            // TODO ERROR init done
            return false;
        }

        if (myInitialPosState.size() == 0)
        {
            // pos not init - set to 0
            if (!initPosition(0))
            {
                return false;
            }
        }

        if (myNetFunctionP.get() == NULL)
        {
            // net function not set - set to identity
            if (!initNetFunction(NetFunctionIdentity::s_getTypeName()))
            {
                return false;
            }
        }

        myPositionLoop.reset(new PositionLoop(myInitialPosState));
        myMotorsLoop.reset(new MotorsLoop(myMotorsInitialState));
        myMainLoop.reset(new MainLoop(myMotorsLoop, myPositionLoop, myNetFunctionP));

        if (myPrintEachNSteps > 0){
            myMainLoop->initPeriodicPrint(&std::cout);
            myMainLoop->setPeriodicPrintFreq(myPrintEachNSteps);
        }

        myInitDone = true;
        return true;
    }

    bool Brain::launch()
    {
        if (!myInitDone)
        {
            // TODO ERROR init not done
            return false;
        }

        if (!myPositionLoop->launch())
        {
            // TODO ERROR "Failed to launch position loop";
            return false;
        }
        if (!myMotorsLoop->launch())
        {
            // TODO ERROR "Failed to launch motors loop";
            return false;
        }
        if (!myMainLoop->launch())
        {
            // TODO ERROR "Failed to launch main loop";
            return false;
        }
        return true;
    }

    void Brain::terminate()
    {
        if (!myInitDone)
        {
            // TODO ERROR init not done
            return;
        }

        myPositionLoop->terminate();
        myMotorsLoop->terminate();
        myMainLoop->terminate();

        myPositionLoop->waitToTerminate();
        myMotorsLoop->waitToTerminate();
        myMainLoop->waitToTerminate();
    }

    bool Brain::s_init()
    {
        // prepare factories
        infra::NetFunction::s_registerType(NetFunctionMul());
        infra::NetFunction::s_registerType(NetFunctionIdentity());
        return true;
    }

}

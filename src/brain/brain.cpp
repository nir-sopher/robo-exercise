#include "brain/brain.h"
#include "brain/net_function_mul.h"

namespace brain
{
    bool Brain::init()
    {
        infra::State initialPosState;
        initialPosState[brain::PositionLoop::POS_KEY] = 1;
        myPositionLoop.reset(new PositionLoop(initialPosState));

        int numMotors = 10;
        infra::State motorsInitialState;
        for (int i = 0; i < numMotors; ++i)
        {
            motorsInitialState[std::to_string(i)] = i;
        }
        myMotorsLoop.reset(new MotorsLoop(motorsInitialState));

        std::shared_ptr<infra::NetFunction> netFunctionP(
            infra::NetFunction::s_getByTypeUnsafe(brain::NetFunctionMul::s_getTypeName()));
        if (netFunctionP.get() == NULL)
        {
            // TODO ERROR - no such type
            return false;
        }

        myMainLoop.reset(new MainLoop(myMotorsLoop, myPositionLoop, netFunctionP));

        return true;
    }

    bool Brain::launch()
    {
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
        return true;
    }

}

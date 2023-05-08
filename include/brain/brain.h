#pragma once

#include <memory>
#include "position_loop.h"
#include "motors_loop.h"
#include "main_loop.h"
#include "net_function_mul.h"

namespace brain
{
    class Brain
    {
    public:
        // initialize the object, load configuration
        bool initPosition(double aInitialPosition);

        bool initAddMotor(const std::string &aMotorId, double aInitialPosition);

        bool initNetFunction(const std::string &aNEtFunctionType);

        bool initDone();

        // start working
        bool launch();

        // done working
        void terminate();

        // program level settings
        static bool s_init();

    private:
        std::shared_ptr<MotorsLoop> myMotorsLoop;
        std::shared_ptr<PositionLoop> myPositionLoop;
        std::shared_ptr<MainLoop> myMainLoop;

        bool myInitDone = false;

        infra::State myInitialPosState;
        infra::State myMotorsInitialState;
        std::shared_ptr<infra::NetFunction> myNetFunctionP;
    };
}

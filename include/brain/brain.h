#pragma once

#include <memory>
#include "position_loop.h"
#include "motors_loop.h"
#include "main_loop.h"

namespace brain
{
    class Brain
    {
    public:
        // initialize the object, load configuration
        bool initPosition(double aInitialPosition);

        // add a motor with the provided initial position
        bool initAddMotor(const std::string &aMotorId, double aInitialPosition);

        // set the "net function". if not set, defualt is the "identity" function
        bool initNetFunction(const std::string &aNEtFunctionType);

        // set mainloop print cycle
        bool initPrintEachNSteps(int64_t aN);

        // get ready to work. must be called before launch but after all "init..." functions
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
        int64_t myPrintEachNSteps = 0;

        bool myInitDone = false;

        infra::State myInitialPosState;
        infra::State myMotorsInitialState;
        std::shared_ptr<infra::NetFunction> myNetFunctionP;
    };
}

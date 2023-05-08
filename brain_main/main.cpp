#include <iostream>
#include "brain/brain.h"

int main()
{
    brain::Brain::s_init();

    brain::Brain brain;
    if (!brain.initPosition(1.2))
    {
        std::cerr << "Failed to init position";
        return -1;
    }

    int numMotors = 10;
    for (int i = 0; i < numMotors; ++i)
    {
        if (!brain.initAddMotor(std::to_string(i), i))
        {
            std::cerr << "Failed to init motor " << i;
            return -1;
        }
    }

    if (!brain.initNetFunction(brain::NetFunctionMul::s_getTypeName()))
    {
        std::cerr << "Failed to brain net function ";
        return -1;
    }

    if (!brain.initDone())
    {
        std::cerr << "Failed to init brain";
        return -1;
    }

    if (!brain.launch())
    {
        std::cerr << "Failed to launch brain";
        return -1;
    }

    std::this_thread::sleep_for(std::chrono::seconds(3));

    brain.terminate();

    return 0;
}
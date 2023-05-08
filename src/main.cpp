#include <iostream>
#include "brain/brain.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;


int main()
{
    brain::Brain::s_init();

    brain::Brain brain;
    if (!brain.init())
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

/*

PYBIND11_MODULE(brain, m) {
    m.doc() = "pybind11 brain plugin"; 
    m.def("main", &main, "Running the brain");
}*/

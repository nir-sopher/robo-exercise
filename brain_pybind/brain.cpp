#include <pybind11/pybind11.h>

namespace py = pybind11;

#include "brain/brain.h"
using namespace brain;

bool init()
{
    return Brain::s_init();
}

PYBIND11_MODULE(brain, m)
{
    m.doc() = "pybind11 brain plugin";

    py::class_<Brain>(m, "Brain")
        .def(py::init<>())
        .def("initPosition", &Brain::initPosition, "Override the initial position. Default is 0")
        .def("initAddMotor", &Brain::initAddMotor, "Define a new motor and its position")
        .def("initNetFunction", &Brain::initNetFunction, "Override the net function. Default is 'identity'")
        .def("initPrintEachNSteps", &Brain::initPrintEachNSteps, "Set printouts each N steps of the main loop")
        .def("initDone", &Brain::initDone, "Mark initialization as done")
        .def("launch", &Brain::launch, "Launch the robot")
        .def("terminate", &Brain::terminate, "Shutdown the robot")
        .def("printState", &Brain::printState, "Print brain state")
        .def("printStatsUnsafe", &Brain::printStatsUnsafe, "Print brain stats. NOT thread safe");

    m.def("init", &init, "A module init function");
}
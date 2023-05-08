#pragma once
#include <random>
#include "infra/stateful_loop.h"

namespace brain
{

    class PositionLoop : public ::infra::StatefulLoop
    {
    public:
        inline static const std::string POS_KEY = "pos";
        PositionLoop(const ::infra::State &aInitialState, int64_t aPeriodUs = 4000);

    protected:
        virtual bool step(infra::State *aStateP) final;

    private:
        inline static double MIN_NOISE_LEVEL = -1;
        inline static double MAX_NOISE_LEVEL = 1;

        std::uniform_real_distribution<double> myNoiseDistribution;
        std::default_random_engine myRandomEngine;
    };
} // namespace
#pragma once

#include <string>
#include <map>
#include "state.h"

namespace infra
{
    class NetFunction
    {
    public:
        // the actual operation of the net-function: return the Motors new state based on the current state and the position
        virtual bool operator()(const State &aMotorsState, const State &aPositionState, State *aOutputMotorsStateP) = 0;

        // factory functions
        static void s_registerType(const NetFunction &aNetFunction);
        static NetFunction *s_getByTypeUnsafe(const std::string &aTypeName);

        // factory supporting functions
        virtual NetFunction *clone() const = 0;
        virtual std::string getTypeName() const = 0;

    private:
        inline static std::map<std::string, const NetFunction *> ourRegistery;
    };

} // namespace
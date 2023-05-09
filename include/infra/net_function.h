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

        // factory supporting instance function - create a new instance
        virtual NetFunction *clone() const = 0;
        // factory supporting instance function - get type name
        virtual std::string getTypeName() const = 0;

        // factory function: register a new type
        static void s_registerType(const NetFunction &aNetFunction);
        // factory function: get by type (NULL if not exists)
        static NetFunction *s_getByTypeUnsafe(const std::string &aTypeName);

    private:
        inline static std::map<std::string, const NetFunction *> ourRegistery;
    };

} // namespace
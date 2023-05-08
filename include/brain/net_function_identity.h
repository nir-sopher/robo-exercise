#pragma once

#include "infra/net_function.h"

namespace brain
{

    class NetFunctionIdentity : public ::infra::NetFunction
    {
    public:
        // the actual operation of the net-function
        virtual bool operator()(const ::infra::State &aMotorsState,
                                const ::infra::State &aPositionState, 
                                ::infra::State *aOutputMotorsStateP) final
        {
            return true;
        }

        // factory supporting functions
        virtual ::infra::NetFunction *clone() const final
        {
            return new NetFunctionIdentity();
        }

        static std::string s_getTypeName()
        {
            return "identity";
        }

        virtual std::string getTypeName() const final
        {
            return s_getTypeName();
        }
    };

} // namespace

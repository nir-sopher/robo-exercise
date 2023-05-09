#pragma once

#include <map>
#include <string>

namespace infra
{
    typedef std::map<std::string, double> State;
} // namespace
std::ostream &operator<<(std::ostream &aOstream, const infra::State &aState);

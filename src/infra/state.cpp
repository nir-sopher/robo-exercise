#include "infra/state.h"

std::ostream &operator<<(std::ostream &aOstream, const infra::State &aState)
{
    for (auto item : aState)
    {
        aOstream << item.first << std::string(":") << std::to_string(item.second) << std::string(" ");
    }
    return aOstream;
}

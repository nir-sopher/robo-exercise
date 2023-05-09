#include "infra/state.h"
#include <ostream>

std::ostream &operator<<(std::ostream &aOstream, const infra::State &aState)
{
    for (auto item : aState)
    {
        aOstream << item.first << ":" << item.second << " ";
    }
    return aOstream;
}

#include "infra/net_function.h"

namespace infra
{
    void NetFunction::s_registerType(const NetFunction &aNetFunction)
    {
        // note: the mempry allocated by the clone would ever be released
        ourRegistery[aNetFunction.getTypeName()] = aNetFunction.clone();
    }

    NetFunction *NetFunction::s_getByTypeUnsafe(const std::string &aTypeName)
    {
        auto found = ourRegistery.find(aTypeName);
        if (found == ourRegistery.end())
        {
            // type not registered
            return NULL;
        }
        return found->second->clone();
    }

} // namespace


#include "infra/int_stats.h"

namespace infra
{

    void IntStats::set(const std::string &aKey, int64_t aVal)
    {
        myData[aKey] = aVal;
    }

    void IntStats::inc(const std::string &aKey, int64_t aVal)
    {
        if (myData.find(aKey) == myData.end())
        {
            set(aKey, 0);
        }
        myData[aKey] += aVal;
    }

    int64_t IntStats::get(const std::string &aKey) const
    {
        auto found = myData.find(aKey);
        if (found == myData.end())
        {
            return -1;
        }
        return found->second;
    }

    std::map<std::string, int64_t> IntStats::getAll() const
    {
        return myData;
    }

    std::ostream &operator<<(std::ostream &aOstream, const infra::IntStats &aIntStats)
    {
        for (auto item : aIntStats.myData)
        {
            aOstream << item.first << std::string(":") << std::to_string(item.second) << std::string(" ");
        }
        return aOstream;
    }
} // namespace

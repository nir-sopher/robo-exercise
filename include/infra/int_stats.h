#pragma once
#include <map>
#include <string>

namespace infra
{
    // Class used forf collecting statitics
    // NOT A MULTI THREADED CLASS
    class IntStats
    {
    public:
        // set the value value for aKey
        void set(const std::string &aKey, int64_t aVal);

        // inc the value value for aKey
        void inc(const std::string &aKey, int64_t aVal);

        // get the value value for aKey
        int64_t get(const std::string &aKey) const;

        // get all values
        std::map<std::string, int64_t> getAll() const;

        friend std::ostream& operator<<(std::ostream& aOstream, const infra::IntStats& aIntStats);

    private:
        std::map<std::string, int64_t> myData;
    };
    
} // namespace
#pragma once
#include <map>
#include <string>

namespace infra
{
    // NOT A MULTI THREADED CLASS
    class IntStats
    {
    public:
        void set(std::string aKey, int64_t aVal);

        void inc(std::string aKey, int64_t aVal);

        int64_t get(std::string aKey) const;

        std::map<std::string, int64_t> getAll() const;

    private:
        std::map<std::string, int64_t> myData;
    };
    
} // namespace
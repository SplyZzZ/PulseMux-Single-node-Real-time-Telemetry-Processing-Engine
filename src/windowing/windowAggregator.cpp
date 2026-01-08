#include "windowing/windowAggregator.h"
#include <algorithm>
#include <chrono>
void update(WindowsData&& data, double value)
{
 ++data.count;
 data.sum += value;
 data.min = std::min(data.min, value);
 data.max = std::max(data.max, value);
}

size_t WindowsKeyHash::operator()(const WindowsKey& k) const noexcept 
{
    size_t h = 0;
    h ^= std::hash<std::string>{}(k.tenant);
    h ^= std::hash<std::string>{}(k.deviceID) << 1;
    h ^= std::hash<std::string>{}(k.metric) << 2;
    h ^= std::hash<long long>{}( k.windowStart.time_since_epoch().count()) << 3;
        return h;
}


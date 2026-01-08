#pragma once
#include <chrono>
#include <string>
struct WindowsKey
{
   std::chrono::time_point<std::chrono::system_clock> windowStart;
    std::string deviceID;
    std::string metric;
    std::string tenant;
    bool operator==(const WindowsKey& other) const = default;
};
struct WindowsData
{
    double min = 0;
    double max = 0;
    double sum = 0;
    uint64_t count = 0;
};
struct WindowsKeyHash {
    size_t operator()(const WindowsKey& k) const noexcept;
};
void update(WindowsData&& data, double value);
#pragma once
#include <chrono>
struct WindowsKey
{
    std::chrono::time_point windowsStart;
    std::string deviceID;
    std::string metric;
    std::string tenant;
};
struct windowsData
{
    double min = 0;
    double max = 0;
    double sum = 0;
    uint64_t count = 0;
};
void update(windowsData&& data, double value);
#pragma once
#pragma once
#include <string>
#include <chrono>

struct Event {
    std::string eventId;
    std::chrono::sys_seconds ts;
    std::chrono::sys_seconds ingestTs;
    std::string tenant;
    std::string deviceId;
    std::string metric;
    double value;
    uint64_t seq;
};
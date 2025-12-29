#pragma once
#include <chrono>
struct TimeContext
{
    std::chrono::sys_seconds epoch{};

    std::chrono::seconds maxClockSkew{10};
    std::chrono::seconds maxIngestFutureSkew{2};
    std::chrono::seconds maxEventFutureSkew{30};
};
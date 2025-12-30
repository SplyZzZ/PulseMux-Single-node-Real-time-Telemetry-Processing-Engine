#pragma once
#include <string>
enum class Unit
{
    Milliseconds,
    Seconds,
    Microseconds,
    Bytes,
    Percent,
    Count,
    Ratio

};
struct MetricInfo {
    Unit unit;
    double scale;
};
const MetricInfo* lookupMetric(std::string_view metric);
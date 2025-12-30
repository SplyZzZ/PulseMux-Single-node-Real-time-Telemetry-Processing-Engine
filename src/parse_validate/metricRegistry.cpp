#include "parse_validate/metricRegistry.h"
#include <unordered_map>
static const std::unordered_map<std::string_view, MetricInfo> registry = 
{
     
    { "latency",         { Unit::Milliseconds, 1.0 } },
    { "latency_s",       { Unit::Seconds,      1000.0 } },
    { "latency_us",      { Unit::Microseconds, 0.001 } },

 
    { "queue_size",      { Unit::Count, 1.0 } },
    { "queue_depth",     { Unit::Count, 1.0 } },
    { "queue_latency",   { Unit::Milliseconds, 1.0 } },

    { "cpu_usage",       { Unit::Percent, 1.0 } },

    { "memory_used",     { Unit::Bytes, 1.0 } },
    { "memory_free",     { Unit::Bytes, 1.0 } },

    { "events_total",    { Unit::Count, 1.0 } },
    { "events_per_second",{ Unit::Ratio, 1.0 } },

    { "network_in_bytes",{ Unit::Bytes, 1.0 } },
    { "network_out_bytes",{ Unit::Bytes, 1.0 } }
};
const MetricInfo* lookupMetric(std::string_view metric)
{
 auto it = registry.find(metric);
 if(it == registry.end()) {return nullptr;}
 return &it->second;
}
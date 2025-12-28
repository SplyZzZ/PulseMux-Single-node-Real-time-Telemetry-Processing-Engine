#include "parse_validate/typeConvertation.h"
#include "parse_validate/event.h"
#include "parse_validate/RawEvent.h"
#include <charconv>
#include <chrono>
Event typeConvertation(const RawEvent& rawEvent)
{
    Event event;
    event.deviceId = std::string(rawEvent.deviceId);
    event.eventId = std::string(rawEvent.eventId);
    event.metric = std::string(rawEvent.metric);
    event.tenant = std::string(rawEvent.tenant);
    {
    auto [ptr, ec] = std::from_chars(rawEvent.value.data(), rawEvent.value.data()+ rawEvent.value.size(), event.value);
    }
    { 
    auto [ptr, ec] = std::from_chars(rawEvent.seq.data(), rawEvent.seq.data()+ rawEvent.seq.size(), event.seq);
    }
    
    std::chrono::sys_seconds parsedTs;
    std::istringstream iss{std::string(rawEvent.ts)};

    iss >> std::chrono::parse("%Y-%m-%d %H:%M:%S", parsedTs);
    event.ts = parsedTs;
    return event;
}
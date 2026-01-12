#include "parse_validate/typeConvertation.h"
#include "parse_validate/event.h"
#include "parse_validate/RawEvent.h"
#include <charconv>
#include <chrono>
#include <sstream>
#include <optional>
#include <date/date.h>

using namespace date;
std::optional<Event> typeConvertation(const RawEvent& rawEvent)
{
    Event event;
    event.deviceId = std::string(rawEvent.deviceId);
    event.eventId = std::string(rawEvent.eventId);
    event.metric = std::string(rawEvent.metric);
    event.tenant = std::string(rawEvent.tenant);
    {
    auto [ptr, ec] = std::from_chars(rawEvent.value.data(), rawEvent.value.data() + rawEvent.value.size(), event.value);
     if (ec != std::errc{} || ptr != rawEvent.value.data() + rawEvent.value.size()) {
        return std::nullopt;
    }
    }
    { 
    auto [ptr, ec] = std::from_chars(rawEvent.seq.data(), rawEvent.seq.data()+ rawEvent.seq.size(), event.seq);
     if (ec != std::errc{} || ptr != rawEvent.seq.data() + rawEvent.seq.size()) {
        return std::nullopt;
    }
    }
    
    std::chrono::sys_seconds parsedTs;

    std::istringstream iss{std::string(rawEvent.ts)};
    iss >> parse("%Y-%m-%dT%H:%M:%SZ", parsedTs);
    if(iss.fail()) {return std::nullopt;}

    event.ts = parsedTs;
    
    std::chrono::sys_seconds parsedIngestTs;

    std::istringstream issT{std::string(rawEvent.ingestTs)};
    issT >> parse("%Y-%m-%dT%H:%M:%SZ", parsedIngestTs);
    if(issT.fail()) {return std::nullopt;}

    event.ingestTs = parsedIngestTs;

    return event;
}

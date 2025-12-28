#include "parse_validate/parseEvent.h"
#include "parse_validate/rawEvent.h"
#include <string>
#include <simdjson.h>
#include <exception>
#include <optional>
#include <chrono>

std::optional<RawEvent> parseEvent(std::string_view line)
{
    static simdjson::dom::parser parser;
    simdjson::dom::element doc;

    if (parser.parse(line).get(doc)){ return std::nullopt;}

    RawEvent event;


    if (doc["device_id"].get(event.deviceId) ||
        doc["event_id"].get(event.eventId)   ||
        doc["tenant"].get(event.tenant)      ||
        doc["metric"].get(event.metric)      ||
        doc["value"].get(event.value)        ||
        doc["seq"].get(event.seq)            ||
        doc["ts"].get(event.ts))
    {
        return std::nullopt;
    }


    return event;
}
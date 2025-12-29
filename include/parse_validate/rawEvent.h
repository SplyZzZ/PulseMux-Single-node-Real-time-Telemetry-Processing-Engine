#pragma once
#include <string>
struct RawEvent {
    std::string_view deviceId;
    std::string_view eventId;
    std::string_view tenant;
    std::string_view metric;
    std::string_view value;
    std::string_view seq;
    std::string_view ts;
    std::string_view ingestTs;
};
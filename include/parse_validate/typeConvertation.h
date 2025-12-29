#pragma once
#include "parse_validate/event.h"
#include "parse_validate/RawEvent.h"
#include <optional>
std::optional<Event> typeConvertation(const RawEvent& rawEvent);
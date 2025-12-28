#pragma once
#include <string>
#include "rawEvent.h"
#include <optional>
std::optional<RawEvent> parseEvent(std::string_view& line);
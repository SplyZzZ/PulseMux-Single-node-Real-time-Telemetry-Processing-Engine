#pragma once
#include <string>
#include <chrono>
bool checkDuplicate(std::string_view eventId, const std::chrono::sys_seconds& ts);
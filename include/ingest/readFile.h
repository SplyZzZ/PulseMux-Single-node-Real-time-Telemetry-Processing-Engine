#pragma once
#include <fstream>
#include <string>
#include <string_view>
#include <functional>
#include "parse_validate/typeConvertation.h"
void readFile(const std::string& path, std::function<void(std::string_view)> onLine);

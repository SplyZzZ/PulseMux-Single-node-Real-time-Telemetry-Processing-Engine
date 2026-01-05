#include "pipeline/router.h"
#include <string>
#include <functional>
size_t router(const std::string& tenant, const std::string& deviceID, const std::string& metric, const size_t countCounter)
{
    size_t h = std::hash(tenant);
    h ^= std::hash(deviceID) + 0x9e3779b97f4a7c15 + (h << 6) + (h >> 2);
    h ^= std::hash(metric) + 0x9e3779b97f4a7c15 + (h << 6) + (h >> 2);
    return h;
}
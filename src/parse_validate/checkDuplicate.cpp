#include "parse_validate/checkDuplicate.h"
#include <unordered_map>
#include <deque>
#include <string>
#include <chrono>
#include <utility>

bool checkDuplicate(std::string_view eventId, const std::chrono::sys_seconds& ts)
{
    static std::unordered_map<std::string, std::chrono::sys_seconds> cache;
    static std::deque<std::pair<std::chrono::sys_seconds, std::string>> order;
    static auto _ = []()
    {
        cache.reserve(10000);
        return 0;
    }(); 
    while(!order.empty())
    {
        const auto& [time, id] = order.front();
        if(ts <= time + std::chrono::seconds{300}) { break;}
        cache.erase(id);
        order.pop_front();
    }

    std::string idCopy(eventId);
    if(cache.contains(idCopy))
    {
        return true;
    }
    cache.try_emplace(idCopy, ts);
    order.emplace_back(ts, std::move(idCopy));
    return false;
}
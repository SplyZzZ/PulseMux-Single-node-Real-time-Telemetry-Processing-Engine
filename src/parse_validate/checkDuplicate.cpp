#include "parse_validate/checkDuplicate.h"
#include <unordered_map>
#include <deque>
#include <string>
#include <chrono>
#include <pair>
static std::unordered_map<std::string, std::chrono::sys_seconds> cache;
cache.reserve(10000);
static std::deque<std::pair<std::chrono::sys_seconds, std::string>> order;
order.reserve(10000);
bool checkDuplicate(std::string_view eventId, const std::chrono::sys_seconds& ts)
{
    while(!order.empty())
    {
        auto [time, id] = order.front();
        if(ts <= time+std::chrono::sys_seconds(300)) { break; }
        if(cache.find(id) != cache.end()) { cache.erase(id);}
        order.pop();
    }
    if(cache.contains(eventId)){return true;}
    //TODO: баг пофіксити 
    cache[eventId] = ts;
    order.emplace(ts, eventId);
    return false;
}
#pragma once
#include <thread>
#include <queue>
#include <mutex>
#include "parse_validate/event.h"
#include <condition_variable>
#include "windowing/windowAggregator.h"
#include <unordered_map>
class Worker
{
public:
    Worker();
    void run();
    ~Worker();
    void set(Event&& event);
    
private:
    bool running_;
    std::thread worker_;
    std::mutex workerMutex_;
    std::condition_variable queueIsReady_;
    std::queue<Event> task_;
    std::unordered_map<WindowsKey, WindowsData, WindowsKeyHash> windows_;
};
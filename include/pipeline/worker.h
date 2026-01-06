#pragma once
#include <thread>
#include <queue>
#include <mutex>
#include "parse_validate/event.h"
#include <condition_variable>
class Worker
{
public:
    void run();
    ~Worker();
    void set(Event&& event);
    
private:
    bool ranning_ = true;
    std::thread worker_;
    std::mutex workerMutex_;
    std::condition_variable queueIsReady_;
    std::queue<Event> task_;
    
}
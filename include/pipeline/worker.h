#pragma once
#include <thread>
#include <queue>
#include <mutex>
#include "parse_validate/event.h"
#include <condition_variable>
#include "windowing/windowAggregator.h"
#include <unordered_map>
#include <chrono>
#include "alerting/cusumState.h"
constexpr std::chrono::seconds WINDOW_SIZE{10};
constexpr std::chrono::seconds LATENESS{5};
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
    std::chrono::sys_seconds maxTimeSeen_;
    std::chrono::sys_seconds watermakr_;
    std::unordered_map<WindowsKey, CusumState, WindowsKeyHash> cusum_;
    void closeWindows(const std::chrono::sys_seconds& watermark);
    void updateCusum(const WindowsKey& key, double avg);
};
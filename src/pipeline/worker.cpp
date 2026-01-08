#include "pipeline/worker.h"
#include <thread>
#include <chrono>
#include <queue>
#include <mutex>
#include "parse_validate/event.h"
#include "parse_validate/normalize.h"
#include "parse_validate/checkDuplicate.h"
constexpr std::chrono::seconds WINDOW_SIZE{10};
Worker::Worker()
{
    running_ = true;
    worker_ = std::thread(&Worker::run, this);
}
void Worker::run()
{
    for(;;)
    {
        std::unique_lock<std::mutex> lock(workerMutex_);
        queueIsReady_.wait(lock, [this]() {
            return !task_.empty() || !running_;
        });
        if(!running_ && task_.empty()) {return;}
        Event ev = std::move(task_.front());
        task_.pop();
        lock.unlock();
        auto scale = normalizationValue(ev.metric);
        // if (!scale) return; TODO:: add log;
        ev.value *= *scale;
        if (checkDuplicate(ev.eventId, ev.ts)) continue; //TODO: return log
        // auto windowsStart = ev.ts - (ev.ts % WINDOWS_SIZE);
    }
    
}
void Worker::set(Event&& event)
{
   std::unique_lock<std::mutex> lock(workerMutex_);
   task_.emplace(std::move(event));
   queueIsReady_.notify_one();
}
Worker::~Worker()
{
    {
    std::lock_guard<std::mutex> lock(workerMutex_);
        running_ = false;
    }
    queueIsReady_.notify_one();
    if(worker_.joinable())
    {
        worker_.join();
    }
}
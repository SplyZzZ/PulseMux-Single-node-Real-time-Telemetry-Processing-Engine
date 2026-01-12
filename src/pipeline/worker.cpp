#include "pipeline/worker.h"
#include <thread>
#include <chrono>
#include <queue>
#include <mutex>
#include <algorithm>
#include "parse_validate/event.h"
#include "parse_validate/normalize.h"
#include "parse_validate/checkDuplicate.h"

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

        auto windowsStart =  ev.ts - (ev.ts.time_since_epoch() % WINDOW_SIZE);

        WindowsKey key;
        key.deviceID = ev.deviceId;
        key.metric = ev.metric;
        key.tenant = ev.tenant;
        key.windowStart = windowsStart;

        auto& isKey = windows_[key];
        update(isKey, ev.value); 

        watermakr_ = (maxTimeSeen_ - LATENESS);
        closeWindows(watermakr_);
        maxTimeSeen_ = std::max(maxTimeSeen_, ev.ts);
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

void Worker::closeWindows(const std::chrono::sys_seconds& watermark)
{
   for(auto it = windows_.begin(); it != windows_.end(); )
   {
        const auto windowsEnd = it->first.windowStart + LATENESS;
        if(windowsEnd <= watermark)
        {
            //it.emit(); TODO: Create function for out data
            updateCusum(it->first, it->second.sum / it->second.count);
            it = windows_.erase(it);
        }
        else
        {
            ++it;
        }
   }
    
}
void Worker::updateCusum(const WindowsKey& key, double avg)
{
    auto& s = cusum_[key];

    if (!s.initialized)
    {
        s.baseline = avg;
        s.initialized = true;
        return;
    }

    constexpr double k = 0.02;   
    constexpr double h = 0.10;   

    s.s_pos = std::max(0.0, s.s_pos + (avg - s.baseline - k * s.baseline));
    s.s_neg = std::max(0.0, s.s_neg + (s.baseline - avg - k * s.baseline));

    if (s.s_pos > h * s.baseline)
    {
        // emitAnomaly(key, "UP", avg, s);
        s.s_pos = 0; 
    }

    if (s.s_neg > h * s.baseline)
    {
        // emitAnomaly(key, "DOWN", avg, s);
        s.s_neg = 0;
    }
    constexpr double alpha = 0.01;
    s.baseline = alpha * avg + (1 - alpha) * s.baseline;
}
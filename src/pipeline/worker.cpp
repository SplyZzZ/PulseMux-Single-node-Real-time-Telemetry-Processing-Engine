#include "pipeline/worker.h"
#include <thread>
#include <queue>
#include <mutex>
#include "parse_validate/event.h"
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
        ranning_ = false;
    }
    queueIsReady_.notify_one();
    if(worker_.joinable)
    {
        worker_.join();
    }
}
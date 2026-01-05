#include "pipeline/worker.h"
#include <thread>
#include <queue>
#include <mutex>
#include "parse_validate/event.h"
void Worker::run()
{
    while(start_)
    {
        Event ev;
        {
            std::lock_guard<std::mutex> lock(workerMutex_);
            if(task_.empty()) { continue;}
            ev = std::move(task_.front());
            task_.pop();
        }
        //TODO : робота воркера
    }
    
   
}
void Worker::set(Event&& event)
{
   std::lock_guard<std::mutex> lock(workerMutex_);
   task_.emplace(std::move(event));
}
Worker::~Worker()
{
    start_ = false;
    if(worker_.joinable)
    {
        worker_.join();
    }
    
}
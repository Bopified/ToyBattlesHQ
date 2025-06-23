#ifndef AC_EVENT_QUEUE_H
#define AC_EVENT_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include "Event.h"

namespace Ac
{
    class ACEventQueue
    {
    private:
        std::queue<std::unique_ptr<ACEvent>> eventQueue;
        mutable std::mutex queueMutex;
        std::condition_variable queueCV;
        std::atomic<bool> shutdownFlag{ false };

    public:
        void pushEvent(std::unique_ptr<ACEvent> event)
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            eventQueue.push(std::move(event));
            queueCV.notify_one();
        }

        std::unique_ptr<ACEvent> popEvent()
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            queueCV.wait(lock, [this]() 
                {
                return !eventQueue.empty() || shutdownFlag.load();
                });

            if (shutdownFlag.load() && eventQueue.empty())
            {
                return nullptr;
            }

            auto event = std::move(eventQueue.front());
            eventQueue.pop();
            return event;
        }

        void shutdown() 
        {
            shutdownFlag.store(true);
            queueCV.notify_all();
        }

        bool empty() const
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            return eventQueue.empty();
        }
    };
}

#endif
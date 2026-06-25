#ifndef EVENTPROCESSOR_H
#define EVENTPROCESSOR_H

#include "Event.h"
#include "ThreadSafeQueue.h"

#include <thread>

class EventProcessor
{
public:

    EventProcessor();

    void start();

    void stop();

    void pushEvent(const Event& event);

private:

    ThreadSafeQueue<Event> queue_;

    std::thread loggerThread_;

    bool running_;

    void loggerWorker();
};

#endif
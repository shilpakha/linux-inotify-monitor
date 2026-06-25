#include "EventProcessor.h"
#include "Logger.h"

#include <thread>
#include <chrono>
#include <iostream>

EventProcessor::EventProcessor()
{
    running_ = false;
}

void EventProcessor::start()
{
    running_ = true;

    loggerThread_ =
        std::thread(
            &EventProcessor::loggerWorker,
            this
        );
        std::cout<< "Main Thread ID: "<< std::this_thread::get_id()<< std::endl;
}

void EventProcessor::stop()
{
    running_ = false;

    queue_.push(Event{});

    loggerThread_.join();
}

void EventProcessor::pushEvent(
    const Event& event)
{
    queue_.push(event);

    std::cout<< "[QUEUE] Event received: "<< event.filename<< std::endl;
}

void EventProcessor::loggerWorker()
{
    Logger logger("../logs/app.log");

    while (running_)
    {
        Event ev = queue_.pop();

        std::this_thread::sleep_for(
            std::chrono::seconds(3)
        );

        logger.logEvent(ev);

        std::cout<< "[LOGGER] Processing: "<< ev.filename<< std::endl;

        std::cout<< "[LOGGER THREAD] "<< ev.filename<< std::endl;
    }
}
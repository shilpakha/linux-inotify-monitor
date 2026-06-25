#ifndef LOGGER_H
#define LOGGER_H

#include<string>
#include "Event.h"

class Logger
{
public:
    Logger(const std::string& filename);

    void logEvent(const Event& event);

private:
    std::string logFile;
};

#endif

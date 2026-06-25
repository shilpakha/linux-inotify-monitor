#include "Logger.h"
#include <fstream>
#include <iostream>

Logger::Logger(const std::string& filename)
{
    logFile = filename;
}

void Logger::logEvent(const Event& event)
{
    std::ofstream file(logFile, std::ios::app);

    if (!file)
    {
        std::cerr << "Cannot open log file\n";
        return;
    }

    file << event.timestamp
         << " "
         << event.action
         << " "
         << event.filename
         << std::endl;
}

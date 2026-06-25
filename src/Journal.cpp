#include "Journal.h"

#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

Journal::Journal(const std::string& folder)
{
    journalFolder = folder;
}

void Journal::saveEvent(const Event& event)
{
    auto now = std::chrono::system_clock::now();

    auto tt = std::chrono::system_clock::to_time_t(now);

    std::tm* tm = std::localtime(&tt);

    std::ostringstream date;

    date << std::put_time(tm, "%Y%m%d");

    std::string fileName =
        journalFolder +
        "/journal_" +
        date.str() +
        ".log";

    std::ofstream file(fileName, std::ios::app);

    if (!file)
        return;

    file << event.timestamp
         << " "
         << event.action
         << " "
         << event.filename
         << std::endl;
}

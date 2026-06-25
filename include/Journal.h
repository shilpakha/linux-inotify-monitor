#ifndef JOURNAL_H
#define JOURNAL_H

#include <string>
#include "Event.h"

class Journal
{
public:
    Journal(const std::string& folder);

    void saveEvent(const Event& event);

private:
    std::string journalFolder;
};

#endif

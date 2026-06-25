#include "../include/InotifyWatcher.h"

#include <iostream>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout
            << "Usage: "
            << argv[0]
            << " <directory>"
            << std::endl;

        return 1;
    }

    std::string path = argv[1];

    InotifyWatcher watcher(path);

    if (!watcher.initialize())
    {
        return 1;
    }

    watcher.startWatching();

    EventProcessor processor;

    processor.start();
    
    return 0;
}

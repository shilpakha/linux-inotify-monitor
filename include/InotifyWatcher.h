#ifndef INOTIFYWATCHER_H
#define INOTIFYWATCHER_H

#include <string>

class InotifyWatcher
{
public:
    InotifyWatcher(const std::string& path);

    bool initialize();

    void startWatching();

private:
    int fd;
    std::string watchPath;
};

#endif

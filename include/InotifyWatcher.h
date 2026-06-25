#ifndef INOTIFYWATCHER_H
#define INOTIFYWATCHER_H

#include <string>
#include <unordered_map>

class InotifyWatcher
{
public:
    InotifyWatcher(const std::string& path);
    ~InotifyWatcher();
    
    bool initialize();

    void startWatching();

private:
    int fd;
    std::string watchPath;

    std::unordered_map<int, std::string> watchMap;

    void addWatchRecursive(const std::string& path);
};

#endif


// #ifndef INOTIFYWATCHER_H
// #define INOTIFYWATCHER_H

// #include <string>

// class InotifyWatcher
// {
// public:
//     InotifyWatcher(const std::string& path);

//     bool initialize();

//     void startWatching();

// private:
//     int fd;
//     std::string watchPath;
// };

// #endif

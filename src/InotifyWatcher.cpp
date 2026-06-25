#include "../include/InotifyWatcher.h"

#include "../include/Event.h"
#include "../include/Logger.h"
#include "../include/Journal.h"

#include <sys/inotify.h>
#include <unistd.h>

#include <iostream>
#include <chrono>
#include <ctime>

#include <filesystem>
#include <unordered_map>

namespace fs = std::filesystem;

InotifyWatcher::InotifyWatcher(const std::string& path)
{
    watchPath = path;
    fd = -1;
}
void InotifyWatcher::addWatchRecursive(const std::string& path)
{
    int wd = inotify_add_watch(
        fd,
        path.c_str(),
        IN_CREATE |
        IN_DELETE |
        IN_MODIFY |
        IN_MOVED_FROM |
        IN_MOVED_TO
    );

    if (wd >= 0)
    {
        watchMap[wd] = path;

        std::cout
            << "Watching: "
            << path
            << std::endl;
    }

    for (const auto& entry :
         fs::recursive_directory_iterator(path))
    {
        if (entry.is_directory())
        {
            int subWd = inotify_add_watch(
                fd,
                entry.path().c_str(),
                IN_CREATE |
                IN_DELETE |
                IN_MODIFY |
                IN_MOVED_FROM |
                IN_MOVED_TO
            );

            if (subWd >= 0)
            {
                watchMap[subWd] =
                    entry.path().string();

                std::cout
                    << "Watching: "
                    << entry.path()
                    << std::endl;
            }
        }
    }
}
bool InotifyWatcher::initialize()
{
    fd = inotify_init1(IN_NONBLOCK);

    if (fd < 0)
    {
        std::cerr << "Failed to initialize inotify\n";
        return false;
    }

    addWatchRecursive(watchPath);

    return true;
}
// bool InotifyWatcher::initialize()
// {
//     fd = inotify_init1(IN_NONBLOCK);

//     if (fd < 0)
//     {
//         std::cerr << "Failed to initialize inotify\n";
//         return false;
//     }

//     int wd = inotify_add_watch(fd,watchPath.c_str(),IN_CREATE |IN_DELETE |IN_DELETE_SELF |IN_MODIFY |IN_MOVED_FROM |IN_MOVED_TO);

//     if (wd < 0)
//     {
//         std::cerr << "Failed to add watch\n";
//         return false;
//     }

//     return true;
// }

void InotifyWatcher::startWatching()
{
    Logger logger("../logs/app.log");
    Journal journal("../journals");

    char buffer[4096];

    std::cout<< "Watching: "<< watchPath<< std::endl;

    while (true)
    {
        int length = read(fd,buffer, sizeof(buffer));

        if (length <= 0)
        {
            usleep(500000);
            continue;
        }

        int i = 0;

        while (i < length)
        {
            struct inotify_event* event = (struct inotify_event*) &buffer[i];

            if (event->len)
            {
                std::cout << "Mask: " << event->mask << std::endl;

                Event ev;

                if ((event->mask & IN_CREATE) && (event->mask & IN_ISDIR))
                {
                    std::string parent = watchMap[event->wd];

                    std::string newDir = parent + "/" + event->name;

                    addWatchRecursive(newDir);

                    std::cout<< "New directory added: "<< newDir<< std::endl;
                }

                // ev.filename = event->name;

                ev.filename = watchMap[event->wd] + "/" + event->name;
                
                if (event->mask & IN_CREATE)
                {
                    ev.action = "CREATED";
                }
                else if (event->mask & IN_DELETE)
                {
                    ev.action = "DELETED";
                }
                else if (event->mask & IN_DELETE_SELF)
                {
                    ev.action = "SELF_DELETED";
                }
                else if (event->mask & IN_MOVED_FROM)
                {
                    ev.action = "MOVED_FROM";
                }
                else if (event->mask & IN_MOVED_TO)
                {
                    ev.action = "MOVED_TO";
                }
                else if (event->mask & IN_MODIFY)
                {
                    ev.action = "MODIFIED";
                }
                else
                {
                    ev.action = "OTHER";
                }

                auto now =
                    std::chrono::system_clock::now();

                auto tt =
                    std::chrono::system_clock::to_time_t(now);

                ev.timestamp = std::ctime(&tt);

                std::cout<< ev.action<< " "<< ev.filename<< std::endl;

                logger.logEvent(ev);

                journal.saveEvent(ev);
            }

            i += sizeof(struct inotify_event) + event->len;
        }
    }
}

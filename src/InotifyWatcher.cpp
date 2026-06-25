#include "../include/InotifyWatcher.h"

#include "../include/Event.h"
#include "../include/Logger.h"
#include "../include/Journal.h"

#include <sys/inotify.h>
#include <unistd.h>

#include <iostream>
#include <chrono>
#include <ctime>


InotifyWatcher::InotifyWatcher(const std::string& path)
{
    watchPath = path;
    fd = -1;
}

bool InotifyWatcher::initialize()
{
    fd = inotify_init1(IN_NONBLOCK);

    if (fd < 0)
    {
        std::cerr << "Failed to initialize inotify\n";
        return false;
    }

    int wd = inotify_add_watch(fd,watchPath.c_str(),IN_CREATE |IN_DELETE |IN_DELETE_SELF |IN_MODIFY |IN_MOVED_FROM |IN_MOVED_TO);

    if (wd < 0)
    {
        std::cerr << "Failed to add watch\n";
        return false;
    }

    return true;
}

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

                ev.filename = event->name;

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

#ifndef SIGNALHANDLER_H
#define SIGNALHANDLER_H

#include <atomic>

extern std::atomic<bool> running;

void setupSignalHandler();

#endif
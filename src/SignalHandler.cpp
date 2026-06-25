#include "SignalHandler.h"

#include <csignal>
#include <iostream>

std::atomic<bool> running(true);

void signalHandler(int signal)
{
    std::cout
        << "\nReceived signal "
        << signal
        << std::endl;

    running = false;
}

void setupSignalHandler()
{
    std::signal(SIGINT, signalHandler);
}
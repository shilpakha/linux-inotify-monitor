cmake_minimum_required(VERSION 3.10)

project(FileMonitor)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)

include_directories(include)

add_executable(
    monitor
    src/main.cpp
    src/Logger.cpp
    src/Journal.cpp
    src/InotifyWatcher.cpp
)

find_package(Threads REQUIRED)

target_link_libraries(
    monitor
    Threads::Threads
)
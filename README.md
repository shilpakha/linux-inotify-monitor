# File Monitor - Linux System Programming Project

## Overview

File Monitor is a Linux system programming project written in C++ that uses the Linux `inotify` API to monitor filesystem events.

The application watches a directory and detects:

* File creation
* File modification
* File deletion

Detected events are:

* Displayed on the console
* Written to a log file
* Stored in daily journal files

---

## Features

* Linux inotify integration
* Event logging
* Journal file generation
* Object-Oriented Design
* CMake build system
* Modern C++ (C++17)

---

## Technologies Used

* C++
* Linux System Programming
* inotify
* CMake
* STL
* File I/O

---

## Project Structure

```text
file_monitor/
│
├── include/
│   ├── Event.h
│   ├── Logger.h
│   ├── Journal.h
│   └── InotifyWatcher.h
│
├── src/
│   ├── main.cpp
│   ├── Logger.cpp
│   ├── Journal.cpp
│   └── InotifyWatcher.cpp
│
├── logs/
├── journals/
├── build/
│
├── CMakeLists.txt
└── README.md
```

---

## Architecture

```text
+----------------+
| InotifyWatcher |
+--------+-------+
         |
         v
      Event
         |
         +------------+
         |            |
         v            v
      Logger      Journal
         |            |
         v            v
     app.log    journal_YYYYMMDD.log
```

---

## Build Instructions

### Install Dependencies

```bash
sudo apt update
sudo apt install build-essential cmake gdb
```

### Build Project

```bash
mkdir build
cd build

cmake ..
make
```

---

## Running the Application

Create a test directory:

```bash
mkdir ../testdir
```

Run:

```bash
./monitor ../testdir
```

Expected output:

```text
Watching: ../testdir
```

---

## Testing

Create a file:

```bash
touch ../testdir/file1.txt
```

Modify a file:

```bash
echo "hello" >> ../testdir/file1.txt
```

Delete a file:

```bash
rm ../testdir/file1.txt
```

Example output:

```text
CREATED file1.txt
MODIFIED file1.txt
DELETED file1.txt
```

---

## Logs

Application log:

```text
logs/app.log
```

Example:

```text
Thu Jun 25 21:00:00 2026 CREATED file1.txt
Thu Jun 25 21:00:10 2026 MODIFIED file1.txt
Thu Jun 25 21:00:20 2026 DELETED file1.txt
```

---

## Journal Files

Daily journals are automatically created:

```text
journals/journal_20260625.log
```

---

## Concepts Demonstrated

* Linux System Calls
* inotify API
* File Monitoring
* Classes and Objects
* Header / Source Separation
* CMake
* File I/O
* Error Handling
* Debugging with gdb

---

## Future Enhancements

* Recursive directory monitoring
* Multithreading
* Thread-safe logging
* Command-line argument parsing
* Signal handling (Ctrl+C)
* Log rotation
* Configuration file support
* JSON output support

---

## Author

Developed as a Linux System Programming and Modern C++ learning project.
# linux-inotify-monitor

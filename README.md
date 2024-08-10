# System Monitor Project

This project is a system monitor application similar to htop, built in C++. It provides real-time insights into the system's processes, CPU utilization, memory usage, and more by parsing information from the /proc filesystem on Linux systems.

# Features

### Process Management:

Displays a list of all running processes with details such as PID, command, user, memory usage, and CPU usage.
Sorts processes by memory usage.

### Real-Time Updates:

Continuously updates the process information to reflect the current state of the system.

### Customizable Display:

The output is structured and easy to read, similar to the popular htop command-line tool.

# Make
This project uses [Make](https://www.gnu.org/software/make/). The Makefile has four targets:
* `build` compiles the source code and generates an executable
* `format` applies [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) to style the source code
* `debug` compiles the source code and generates an executable, including debugging symbols
* `clean` deletes the `build/` directory, including all of the build artifacts

# Instructions

1. Clone the project repository: `git clone https://github.com/ghaidaasamir/System-Monitor.git`

2. sudo apt-get install clang-format
3. Build the project: `make build`

4. Run the resulting executable: `./build/monitor`
![Starting System Monitor](images/starting_monitor.png)

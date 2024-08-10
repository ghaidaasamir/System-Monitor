#include "cpu.h"

void CPU::readProcsRunning() {
  std::ifstream file("/proc/stat");
  std::string line;
  procsRunning = 0;
  totalProcesses = 0;
  while (std::getline(file, line)) {
    if (line.find("procs_running") == 0) {
      procsRunning = std::stoi(line.substr(line.find(" ") + 1));
    } else {
      if (line.find("processes") == 0) {
        totalProcesses = std::stoi(line.substr(line.find(" ") + 1));
      }
    }
  }
  file.close();
}

int CPU::ProcsRunning() { return procsRunning; }

int CPU::TotalProcesses() { return totalProcesses; }

double CPU::utilization() {
  long active_jiffies = 0;
  long total_jiffies = 0;
  active_jiffies = cpustats.userTime + cpustats.niceTime + cpustats.systemTime +
                   cpustats.irqTime + cpustats.softirqTime + cpustats.stealTime;
  total_jiffies = cpustats.totalTime;
  return static_cast<double>(active_jiffies) / total_jiffies;
}

void CPU::cpuUtilization() {
  std::ifstream inputFile("/proc/stat");
  std::string line;

  std::getline(inputFile, line);
  parseCPUStatLine(line);
  readProcsRunning();
}

void CPU::displayCPUStats() {
  std::cout << "CPU: " << cpustats.cpuLabel << std::endl;
  std::cout << "User Time: " << cpustats.userTime << std::endl;
  std::cout << "Nice Time: " << cpustats.niceTime << std::endl;
  std::cout << "System Time: " << cpustats.systemTime << std::endl;
  std::cout << "Idle Time: " << cpustats.idleTime << std::endl;
  std::cout << "IO Wait Time: " << cpustats.iowaitTime << std::endl;
  std::cout << "IRQ Time: " << cpustats.irqTime << std::endl;
  std::cout << "SoftIRQ Time: " << cpustats.softirqTime << std::endl;
  std::cout << "Steal Time: " << cpustats.stealTime << std::endl;
  std::cout << "Guest Time: " << cpustats.guestTime << std::endl;
  std::cout << "Guest Nice Time: " << cpustats.guestNiceTime << std::endl;
  std::cout << "Total Time: " << cpustats.totalTime << std::endl;
  std::cout << "Non-Idle Percentage: " << cpustats.nonIdlePercentage()
            << std::endl;
  std::cout << "--------------------------------------" << std::endl;

  std::cout << "Running Processes: " << ProcsRunning() << std::endl;
  std::cout << "Total Processes: " << TotalProcesses() << std::endl;
}

void CPU::parseCPUStatLine(const std::string& line) {
  std::istringstream cpudata(line);
  cpudata >> cpustats.cpuLabel >> cpustats.userTime >> cpustats.niceTime >>
      cpustats.systemTime >> cpustats.idleTime >> cpustats.iowaitTime >>
      cpustats.irqTime >> cpustats.softirqTime >> cpustats.stealTime >>
      cpustats.guestTime >> cpustats.guestNiceTime;
  cpustats.calculateTotalTime();
}

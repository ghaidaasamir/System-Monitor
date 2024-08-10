#ifndef CPU_H
#define CPU_H

#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

class CPU {
 public:
  struct CPUStats {
    std::string cpuLabel;  // CPU label (e.g., "cpu0", "cpu1")
    double userTime;       // Time spent in user mode
    double niceTime;       // Time spent in user mode with low priority
    double systemTime;     // Time spent in system mode
    double idleTime;       // Time spent idle
    double iowaitTime;     // Time spent waiting for I/O
    double irqTime;        // Time spent handling hardware interrupts
    double softirqTime;    // Time spent handling software interrupts
    double stealTime;      // Time spent in other virtual machines
    double guestTime;      // Time spent running a virtual CPU
    double guestNiceTime;  // Time spent running a virtual CPU with low priority
    double totalTime;      // Total time (sum of all times)

    double nonIdlePercentage() const {
      return (1.0 - (idleTime / totalTime)) * 100;
    }

    double calculateTotalTime() {
      totalTime = userTime + niceTime + systemTime + idleTime + iowaitTime +
                  irqTime + softirqTime + stealTime + guestNiceTime + guestTime;
      return totalTime;
    }
  };
  void readCPUStats();
  double calculateCPUUsage(const CPUStats& prev, const CPUStats& curr);
  void readProcsRunning();
  int ProcsRunning();
  int TotalProcesses();
  double utilization();
  void cpuUtilization();
  void displayCPUStats();

 private:
  int procsRunning;
  int totalProcesses;
  CPUStats cpustats;
  std::vector<CPUStats> cpuDataList;
  void parseCPUStatLine(const std::string& line);
};

#endif  // CPU_H

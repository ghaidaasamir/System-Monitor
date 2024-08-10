#ifndef HTOP_H
#define HTOP_H

#include <string>

#include "cpu.h"
#include "disk.h"
#include "memory.h"
#include "network.h"
#include "process.h"

class HTOP {
 public:
  HTOP();
  std::string OperatingSystem();
  std::string Kernel();
  float MemoryUtilization();
  float Utilization();
  int TotalProcesses();
  int RunningProcesses();
  std::vector<PROCESS> Processes();
  long int UpTime();

 private:
  MEMORY memory;
  CPU cpu;
  PROCESS process;
};

#endif
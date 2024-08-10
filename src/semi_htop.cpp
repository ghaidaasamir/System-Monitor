#include "semi_htop.h"

HTOP::HTOP() {
  memory.readMemoryStats();
  cpu.cpuUtilization();
  process.readAllProcess();
}

std::string HTOP::OperatingSystem() { return SYSTEM::operatingSystem(); }

std::string HTOP::Kernel() { return SYSTEM::Kernel(); }

float HTOP::MemoryUtilization() { return memory.memoryUtilization(); }

float HTOP::Utilization() { return cpu.utilization(); }

int HTOP::TotalProcesses() { return cpu.TotalProcesses(); }

int HTOP::RunningProcesses() { return cpu.ProcsRunning(); }

std::vector<PROCESS> HTOP::Processes() { return process.getProcesses(); }

long int HTOP::UpTime() { return SYSTEM::upTime(); }

#ifndef PROCESS_H
#define PROCESS_H

#include <dirent.h>

#include <algorithm>
#include <cctype>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "system.h"

class PROCESS {
 public:
  PROCESS();
  PROCESS(int pid);

  struct ProcessStats {
    int pid;
    std::string name;
    double cpuUsage;
    double memory;
    double residentSetSize{0};
    double utime;
    double stime;
    int runningProcesses;
  };

  struct ProcessStatus {
    int pid;
    std::string user{"Unkown"};
    std::string command{"Unkown"};
    std::string ram{"0"};
    std::string uid{"0"};
  };

  int pid() const;
  std::string getRam() const;
  std::string getUID() const;
  std::string getUserFromUID() const;
  float cpuUtilization() const;
  long int upTime() const;
  std::string getCommand() const;

  void displayProcessStatus();
  void readAllProcess();
  void parseProcessStat();
  void parseProcessStatus();
  std::vector<PROCESS> getProcesses();
  std::vector<int> pids();
  bool operator<(PROCESS const& a) const;
  std::map<std::string, ProcessStats> ProcessStatsMap;
  std::map<std::string, ProcessStatus> ProcessStatusMap;

 private:
  int pId;
  std::vector<PROCESS> processes_;
  std::vector<int> pids_list;
  ProcessStats process_data;
  ProcessStatus process_status;
  void parseProcessStatusLine(const std::string& line);
  void parseCommand();
  void parseUserFromUID();
  void parseProcessStatLine(const std::string& line);
  float getProcessStats() const;
  std::vector<int> getRunningPids();
};

#endif  // PROCESS_H

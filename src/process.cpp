#include "process.h"

PROCESS::PROCESS() {}

PROCESS::PROCESS(int pid) : pId(pid) {}

int PROCESS::pid() const { return pId; }

void PROCESS::parseProcessStatus() {
  std::ifstream inputFile("/proc/" + std::to_string(pId) + "/status");
  std::string line;
  process_status.pid = pId;
  while (std::getline(inputFile, line)) {
    parseProcessStatusLine(line);
  }
  parseCommand();
  parseUserFromUID();
  ProcessStatusMap[std::to_string(pId)] = process_status;
}

void PROCESS::parseProcessStat() {
  std::ifstream inputFile("/proc/" + std::to_string(pId) + "/stat");
  std::string line;
  process_data.pid = pId;
  if (std::getline(inputFile, line)) {
    parseProcessStatLine(line);
  }
  ProcessStatsMap[std::to_string(pId)] = process_data;
}

std::string PROCESS::getRam() const { return process_status.ram; }

std::string PROCESS::getUserFromUID() const { return process_status.user; }

std::string PROCESS::getUID() const { return process_status.uid; }

std::string PROCESS::getCommand() const { return process_status.command; }

void PROCESS::displayProcessStatus() {
  std::cout << "PID: " << pid() << std::endl;
  std::cout << "User: " << getUserFromUID() << std::endl;
  std::cout << "UID: " << getUID() << std::endl;
  std::cout << "RAM Usage: " << getRam() << std::endl;
  std::cout << "Command: " << getCommand() << std::endl;
  std::cout << "----------------------" << std::endl;
}

void displayAllProcessStatus(
    std::map<std::string, PROCESS::ProcessStatus> ProcessStatusMap) {
  for (const auto& pair : ProcessStatusMap) {
    auto& stats = pair.second;
    std::cout << "For process id: " << pair.first << std::endl;
    std::cout << "PID: " << stats.pid << std::endl;
    std::cout << "User: " << stats.user << std::endl;
    std::cout << "UID: " << stats.uid << std::endl;
    std::cout << "Command: " << stats.command << std::endl;
    std::cout << "Ram: " << stats.ram << std::endl;
    std::cout << "---------------------------" << std::endl;
  }
}

void PROCESS::parseProcessStatusLine(const std::string& line) {
  std::istringstream Processdata(line);
  std::string key, value;
  Processdata >> key >> value;
  key.pop_back();

  if (key == "Uid") {
    process_status.uid = value;
    return;
  }
  if (key == "VmSize") {
    process_status.ram = std::to_string(std::stoi(value) / 1024);
    return;
  }
}

void PROCESS::parseCommand() {
  std::ifstream commFile("/proc/" + std::to_string(pId) + "/cmdline");
  std::string command;
  std::getline(commFile, command);
  process_status.command = command;
}

void PROCESS::parseUserFromUID() {
  std::string line;
  std::string name, _, uid, Uid;
  Uid = process_status.uid;
  std::ifstream stream("/etc/passwd");
  while (std::getline(stream, line)) {
    std::replace(line.begin(), line.end(), ':', ' ');
    std::istringstream linestream(line);
    linestream >> name >> _ >> uid;
    if (uid == Uid) {
      process_status.user = name;
      break;
    }
  }
}

bool PROCESS::operator<(PROCESS const& a) const {
  return std::stol(getRam()) < std::stol(a.getRam());
}

float PROCESS::getProcessStats() const {
  return process_data.stime + process_data.utime;
}

long int PROCESS::upTime() const {
  return SYSTEM::upTime() - process_data.residentSetSize;
}

std::vector<int> PROCESS::pids() { return getRunningPids(); }

std::vector<int> PROCESS::getRunningPids() {
  std::vector<int> running_pids;
  DIR* pDir = opendir("/proc");
  dirent* file;

  if (pDir) {
    while ((file = readdir(pDir))) {
      if (!isdigit(file->d_name[0]) || strcmp(file->d_name, ".") == 0 ||
          strcmp(file->d_name, "..") == 0) {
        continue;
      }
      int pid = std::stoi(file->d_name);
      running_pids.push_back(pid);
    }
    closedir(pDir);
  }

  return running_pids;
}

void PROCESS::readAllProcess() {
  DIR* pDir;
  pDir = opendir("/proc");
  dirent* file;
  if (pDir) {
    while ((file = readdir(pDir))) {
      if (!isdigit(file->d_name[0]) || strcmp(file->d_name, ".") == 0 ||
          strcmp(file->d_name, "..") == 0) {
        continue;
      }

      PROCESS process(std::stoi(file->d_name));
      process.parseProcessStat();
      process.parseProcessStatus();
      processes_.push_back(process);

    }
  }

  closedir(pDir);
}

float PROCESS::cpuUtilization() const {
  float act_time = getProcessStats() / 100.f;
  float up_time = float(upTime());
  float util = act_time / up_time;
  return util;
}

void displayAllProcessStats(
    std::map<std::string, PROCESS::ProcessStats> ProcessStatsMap) {
  std::cout << "ProcessStatsMap size: " << ProcessStatsMap.size() << std::endl;
  for (const auto& pair : ProcessStatsMap) {
    const auto& stats = pair.second;
    std::cout << "For process id: " << pair.first << std::endl;
    std::cout << "PID: " << stats.pid << std::endl;
    std::cout << "Name: " << stats.name << std::endl;
    std::cout << "CPU Usage: " << stats.cpuUsage << std::endl;
    std::cout << "Memory: " << stats.memory << std::endl;
    std::cout << "---------------------------" << std::endl;
  }
}

void PROCESS::parseProcessStatLine(const std::string& line) {
  std::istringstream Processdata(line);
  std::istream_iterator<std::string> begin(Processdata), end;
  std::vector<std::string> tokens(begin, end);
  if (line.find("procs_running") == 0) {
    process_data.runningProcesses = std::stoi(line.substr(line.find(" ") + 1));
  }
  if (tokens.size() > 24) {
    process_data.pid = std::stoi(tokens[0]);
    process_data.name = tokens[1].substr(1, tokens[1].find(")") - 1);
    double utime = std::stod(tokens[13]);
    double stime = std::stod(tokens[14]);
    process_data.utime = utime;
    process_data.stime = stime;
    process_data.cpuUsage = utime + stime;
    process_data.memory = std::stod(tokens[23]);
    process_data.residentSetSize = std::stod(tokens[21]);
  }
}

std::vector<PROCESS> PROCESS::getProcesses() {
  std::sort(processes_.begin(), processes_.end(), [](PROCESS p1, PROCESS p2) {
    return p1.cpuUtilization() > p2.cpuUtilization();
  });
  return processes_;
}

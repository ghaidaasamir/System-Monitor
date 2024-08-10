#include "system.h"

namespace SYSTEM {

std::string Kernel() {
  std::ifstream file("/proc/version");
  std::string kernel, version, _;
  if (file.is_open()) {
    std::getline(file, kernel);
    std::istringstream s(kernel);
    s >> _ >> _ >> version;
    file.close();
  }
  return version;
}

std::string operatingSystem() {
  std::ifstream file("/etc/os-release");
  std::string line;
  std::string os;
  while (std::getline(file, line)) {
    if (line.find("NAME=") == 0) {
      os = line.substr(5);
      if (os.front() == '\"' && os.back() == '\"') {
        os = os.substr(1, os.size() - 2);
      }
      break;
    }
  }
  file.close();
  return os;
}

long int upTime() {
  std::string uptime;
  std::string line;
  std::ifstream stream("/proc/uptime");
  std::getline(stream, line);
  std::istringstream linestream(line);
  linestream >> uptime;
  return stol(uptime);
}

}
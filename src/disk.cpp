#include "disk.h"

struct DISK::DiskStats {
  std::string deviceName;
  double readsCompleted;
  double readsMerged;
  double sectorsRead;
  double timeReading;
  double writesCompleted;
  double writesMerged;
  double sectorsWritten;
  double timeWriting;
  double readRate;   // Bytes per second
  double writeRate;  // Bytes per second
};

void DISK::readDiskStats() {
  std::ifstream inputFile("/proc/diskstats");
  std::string line;
  DiskStats disk_data;

  while (std::getline(inputFile, line)) {
    disk_data = parseDiskStatLine(line);
    disk_datalist.push_back(disk_data);
  }
}

void DISK::displayDiskStats() {
  for (const auto& stats : disk_datalist) {
    std::cout << "Device Name: " << stats.deviceName << std::endl;
    std::cout << "Reads Completed: " << stats.readsCompleted << std::endl;
    std::cout << "Reads Merged: " << stats.readsMerged << std::endl;
    std::cout << "Sectors Read: " << stats.sectorsRead << std::endl;
    std::cout << "Time Spent Reading (ms): " << stats.timeReading << std::endl;
    std::cout << "Writes Completed: " << stats.writesCompleted << std::endl;
    std::cout << "Writes Merged: " << stats.writesMerged << std::endl;
    std::cout << "Sectors Written: " << stats.sectorsWritten << std::endl;
    std::cout << "Time Spent Writing (ms): " << stats.timeWriting << std::endl;
    std::cout << "-----------------------------------" << std::endl;
  }
}

DISK::DiskStats DISK::parseDiskStatLine(const std::string& line) {
  DiskStats disk_data;
  std::istringstream Diskdata(line);
  std::string garbage;
  Diskdata >> garbage >> garbage >> disk_data.deviceName >>
      disk_data.readsCompleted >> disk_data.readsMerged >>
      disk_data.sectorsRead >> disk_data.timeReading >>
      disk_data.writesCompleted >> disk_data.writesMerged >>
      disk_data.sectorsWritten >> disk_data.timeWriting;

  return disk_data;
}
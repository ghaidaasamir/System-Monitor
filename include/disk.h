#ifndef DISK_H
#define DISK_H

#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

class DISK {
 public:
  struct DiskStats;
  void readDiskStats();
  void displayDiskStats();

 private:
  std::vector<DiskStats> disk_datalist;
  DiskStats parseDiskStatLine(const std::string& line);
};

#endif  // DISK_H

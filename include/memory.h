#ifndef MEMORY_H
#define MEMORY_H

#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

class MEMORY {
 public:
  struct MemoryStats {
    double swapTotal;
    double swapFree;
    double cacheMemory;
    double bufferMemory;
    double availableMemory;
    double freeMemory;
    double totalMemory;
  };
  void readMemoryStats();
  void displayMemoryStats();
  float memoryUtilization();

 private:
  MemoryStats memory_data;
  void parseMemoryStatLine(const std::string& line);
};

#endif  // MEMORY_H

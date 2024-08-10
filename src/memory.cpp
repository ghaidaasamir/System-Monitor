#include "memory.h"

void MEMORY::readMemoryStats() {
  std::ifstream inputFile("/proc/meminfo");
  std::string line;

  while (std::getline(inputFile, line)) {
    parseMemoryStatLine(line);
  }
}

void MEMORY::displayMemoryStats() {
  std::cout << "Total: " << memory_data.totalMemory << " kB" << std::endl;
  std::cout << "Free: " << memory_data.freeMemory << " kB" << std::endl;
  std::cout << "Available: " << memory_data.availableMemory << " kB"
            << std::endl;
  std::cout << "Buffers: " << memory_data.bufferMemory << " kB" << std::endl;
  std::cout << "Cached: " << memory_data.cacheMemory << " kB" << std::endl;
  std::cout << "SwapTotal: " << memory_data.swapTotal << " kB" << std::endl;
  std::cout << "SwapFree: " << memory_data.swapFree << " kB" << std::endl;
}

float MEMORY::memoryUtilization() {
  return static_cast<float>(memory_data.totalMemory - memory_data.freeMemory) /
         static_cast<float>(memory_data.totalMemory);
}

void MEMORY::parseMemoryStatLine(const std::string& line) {
  std::istringstream Memorydata(line);
  std::istream_iterator<std::string> begin(Memorydata), end;
  std::vector<std::string> tokens(begin, end);

  if (tokens.size() >= 2) {
    std::string s = tokens[0];
    double value = std::stod(tokens[1]);
    if (s == "MemTotal:") {
      memory_data.totalMemory = value;
    } else if (s == "MemFree:") {
      memory_data.freeMemory = value;
    } else if (s == "MemAvailable:") {
      memory_data.availableMemory = value;
    } else if (s == "Buffers:") {
      memory_data.bufferMemory = value;
    } else if (s == "Cached:") {
      memory_data.cacheMemory = value;
    } else if (s == "SwapTotal:") {
      memory_data.swapTotal = value;
    } else if (s == "SwapFree:") {
      memory_data.swapFree = value;
    }
  }
}
#ifndef NETWORK_H
#define NETWORK_H

#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

class NETWORK {
 public:
  struct NetworkStats;
  void calculateNetworkRates(NetworkStats& previous, NetworkStats& current);
  void readNetworkStats();
  void displayNetworkStats();

 private:
  std::vector<NetworkStats> network_datalist;
  NetworkStats parseNetworkStatLine(const std::string& line);
};

#endif  // NETWORK_H

#include "network.h"

struct NETWORK::NetworkStats {
  std::string
      interfaceName;        // Name of the network interface (e.g., eth0, wlan0)
  double bytesReceived;     // Total bytes received
  double bytesTransmitted;  // Total bytes transmitted
  double packetsReceived;   // Total packets received
  double packetsTransmitted;  // Total packets transmitted
  double receiveErrors;       // Number of receive errors
  double transmitErrors;      // Number of transmit errors
  double collisions;          // Number of collisions
  double droppedPackets;      // Number of dropped packets
  double receiveRate = 0;     // Calculated rate of bytes received per second
  double transmitRate = 0;    // Calculated rate of bytes transmitted per second
};

void NETWORK::calculateNetworkRates(NetworkStats& previous,
                                    NetworkStats& current) {
  double intervalSeconds = 1.0;
  current.receiveRate =
      (current.bytesReceived - previous.bytesReceived) / intervalSeconds;
  current.transmitRate =
      (current.bytesTransmitted - previous.bytesTransmitted) / intervalSeconds;
}

void NETWORK::readNetworkStats() {
  std::ifstream inputFile("/proc/net/dev");
  std::string line;
  NetworkStats network_data;

  std::getline(inputFile, line);
  std::getline(inputFile, line);

  while (std::getline(inputFile, line)) {
    network_data = parseNetworkStatLine(line);
    network_datalist.push_back(network_data);
  }
}

void NETWORK::displayNetworkStats() {
  for (const auto& stats : network_datalist) {
    std::cout << "Interface: " << stats.interfaceName << std::endl;
    std::cout << "Bytes Received: " << stats.bytesReceived << std::endl;
    std::cout << "Bytes Transmitted: " << stats.bytesTransmitted << std::endl;
    std::cout << "Packets Received: " << stats.packetsReceived << std::endl;
    std::cout << "Packets Transmitted: " << stats.packetsTransmitted << std::endl;
    std::cout << "Receive Errors: " << stats.receiveErrors << std::endl;
    std::cout << "Transmit Errors: " << stats.transmitErrors << std::endl;
    std::cout << "Collisions: " << stats.collisions << std::endl;
    std::cout << "Dropped Packets: " << stats.droppedPackets << std::endl;
    std::cout << "----------------------" << std::endl;
  }
}

NETWORK::NetworkStats NETWORK::parseNetworkStatLine(const std::string& line) {
  NetworkStats network_data;
  std::istringstream Networkdata(line);
  std::istream_iterator<std::string> begin(Networkdata), end;
  std::vector<std::string> tokens(begin, end);

  network_data.interfaceName = tokens[0].substr(0, tokens[0].find(":"));
  network_data.bytesReceived = std::stod(tokens[1]);
  network_data.packetsReceived = std::stod(tokens[2]);
  network_data.bytesTransmitted = std::stod(tokens[9]);
  network_data.packetsTransmitted = std::stod(tokens[10]);
  network_data.receiveErrors = std::stod(tokens[3]);
  network_data.transmitErrors = std::stod(tokens[11]);
  network_data.collisions = std::stod(tokens[13]);
  network_data.droppedPackets = std::stod(tokens[4]);

  return network_data;
}
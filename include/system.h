#ifndef SYSTEM_H
#define SYSTEM_H

#include <sys/sysinfo.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace SYSTEM {

std::string Kernel();
std::string operatingSystem();
long int upTime();

} 

#endif  // SYSTEM_H

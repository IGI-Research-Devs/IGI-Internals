#pragma once

//#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
/*Defining WIN32 Constants*/
#undef WIN32_LEAN_AND_MEAN  
#include <windows.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <functional>
#include <ostream>
#include <string>
#include <map>
#include <functional>
#include <list>
#include <memory>
#include <type_traits>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <iomanip>
#include <array>
using std::string;
#define HexFmtAddr(addr) std::setw(8) << std::setfill('0') << std::uppercase << std::hex << addr
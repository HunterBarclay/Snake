#pragma once

#include <iostream>

#define DEBUG 1

#if DEBUG
#define LOG(x) std::cout << "[Info] " << x << std::endl;
#define WARN(x) std::cout << "[Warning] " << x << std::endl;
#else
#define LOG(x)
#define WARN(x)
#endif
#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

// Some huge, never-changing standard headers and third-party headers
// in order to create precompiled header-files.

#ifdef _WIN32

#include <windows.h>
// Work around the legendary min-max-problem, macro-magic ruining std::C++
#undef min
#undef max

#endif

#include "debug_log.h"
#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <climits>
#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdint>
#include <cwchar>
#include <fstream>
#include <iostream>
#include <mutex>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

// To be used in assertions
constexpr bool NOT_YET_IMPLEMENTED = false;
constexpr bool THIS_MUST_NOT_HAPPEN = false;


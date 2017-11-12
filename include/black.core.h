#pragma once


// Black Framework main namespace.
namespace Black
{
// Core library.
namespace Core
{}
}

// Environment configuration.
#include "core/types.h"
#include "core/configuration.h"

// Make some of STL stuff included by default.
#include <stdint.h>
#include <stdarg.h>
#include <cstdint>
#include <cstdarg>
#include <csignal>
#include <exception>
#include <limits>
#include <locale>
#include <codecvt>
#include <string>
#include <ostream>
#include <array>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <memory>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <typeinfo>

// Most basic third-party libraries.
#include <fmt/format.h>
#include <fmt/ostream.h>

// Include core stuff.
#include "core/constants.h"
#include "core/macros.h"

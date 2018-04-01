#pragma once


// Black Framework main namespace.
namespace Black
{
// Core library.
inline namespace Core
{

}
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
#include <typeindex>

// Most core third-party libraries.
#include <fmt/format.h>
#include <fmt/ostream.h>

// Most core stuff.
#include "core/constants.h"
#include "core/macros.h"
#include "type-traits/std-constants.h"
#include "type-traits/std-types.h"
#include "types/generic-types.h"
#include "utils/generic-utils.h"

// Core types.
#include "types/NotNull.h"
#include "types/PlainView.h"
#include "types/PlainVector.h"
#include "types/StringView.h"
#include "types/EnumFlags.h"
#include "types/IntrusiveHook.h"
#include "types/IntrusiveLink.h"
#include "types/RingBuffer.h"
#include "types/StaticString.h"
#include "types/DebugName.h"
#include "types/ScopedPointer.h"

// Core utils.
#include "utils/platform-utils.h"
#include "utils/container-utils.h"
#include "utils/text-utils.const.h"
#include "utils/text-utils.h"
#include "utils/tuple-utils.h"
#include "utils/hash-utils.h"

// Type traits.
#include "type-traits/StaticStrings.Join.h"
#include "type-traits/StaticStrings.IsEqual.h"
#include "type-traits/StaticStrings.Bisect.h"
#include "type-traits/StaticStrings.RemoveSufix.h"
#include "type-traits/StaticStrings.RemovePrefix.h"
#include "type-traits/StaticStrings.IsStartsWith.h"
#include "type-traits/StaticStrings.IsEndsWith.h"
#include "type-traits/StaticStrings.Substring.h"

// Core subsystems.
#include "concurrency/concurrency.h"

// Platform-specific definitions.
#include "platform/platform.h"

// Inline implementations.
#include "utils/hash-utils.inl"
#include "utils/tuple-utils.inl"
#include "utils/text-utils.inl"
#include "utils/container-utils.plain-containers.inl"
#include "utils/container-utils.set.inl"
#include "utils/container-utils.map.inl"
#include "utils/container-utils.unordered_map.inl"
#include "utils/platform-utils.inl"

#include "types/RingBuffer.inl"
#include "types/IntrusiveLink.inl"
#include "types/PlainVector.inl"
#include "types/PlainView.inl"

#include "utils/generic-utils.inl"

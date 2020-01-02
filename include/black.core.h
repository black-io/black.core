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
#include <uchar.h>
#include <cstdint>
#include <cstdarg>
#include <csignal>
#include <cstdlib>
#include <exception>
#include <limits>
#include <locale>
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
#include <functional>
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
#include "utils/generic-utils.h"
#include "types/generic-types.h"
#include "utils/time-utils.h"

// Core types.
#include "types/NotNull.h"
#include "types/PlainView.h"
#include "types/PlainVector.h"
#include "types/StringView.h"
#include "types/EnumFlags.struct.h"
#include "types/EnumFlags.internal.h"
#include "types/EnumFlags.h"
#include "types/IntrusiveHook.h"
#include "types/IntrusiveLink.h"
#include "types/RingBuffer.h"
#include "types/StaticString.h"
#include "types/DebugName.h"
#include "types/ScopedPointer.h"

// Generic bit view.
#include "types/BitView.internal.h"
#include "types/BitView.iterator.h"
#include "types/BitView.h"

// Generic static list.
#include "types/StaticList.forwards.h"
#include "types/StaticList.internal.h"
#include "types/StaticList.iterator.h"
#include "types/StaticListNode.h"
#include "types/StaticList.h"

// Core utils.
#include "utils/platform-utils.h"
#include "utils/container-utils.h"
#include "utils/text-utils.internal.h"
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
#include "utils/text-utils.split-string.inl"
#include "utils/container-utils.plain-containers.inl"
#include "utils/container-utils.set.inl"
#include "utils/container-utils.map.inl"
#include "utils/container-utils.unordered_map.inl"
#include "utils/platform-utils.inl"

#include "types/BitView.inl"
#include "types/BitView.iterator.inl"
#include "types/BitView.internal.inl"
#include "types/StaticList.inl"
#include "types/StaticListNode.inl"
#include "types/StaticList.iterator.inl"
#include "types/StaticList.internal.inl"
#include "types/RingBuffer.inl"
#include "types/IntrusiveLink.inl"
#include "types/PlainVector.inl"
#include "types/PlainView.inl"

#include "utils/generic-utils.inl"

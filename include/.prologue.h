#pragma once


// The library namespace definition.
#include ".bootstrap/namespace.h"

// Environment configuration.
#include ".bootstrap/types.h"
#include ".bootstrap/configuration.h"

// Persistent external stuff.
#include ".bootstrap/persistent-std.h"
#include ".bootstrap/persistent-third-party.h"

// Most global stuff.
#include ".bootstrap/constants.h"
#include ".bootstrap/macros.h"
#include "global/algorithms/misc.h"
#include "global/algorithms/bytes.h"
#include "global/algorithms/memory.h"
#include "global/types/generic-types.h"
#include "global/types/generic-types.aliasing.h"
#include "global/algorithms/time.h"

// Global types.
#include "global/core-guidelines/NotNull.h"
#include "global/types/PlainView.h"
#include "global/types/PlainVector.h"
#include "global/types/IntrusiveHook.h"
#include "global/types/IntrusiveLink.h"
#include "global/types/RingBuffer.h"
#include "global/types/DebugName.h"
#include "global/types/ScopedPointer.h"

#include "global/types/EnumFlags.struct.h"
#include "global/types/EnumFlags.internal.h"
#include "global/types/EnumFlags.h"

// Platform-specific definitions.
#include "platform/platform.h"

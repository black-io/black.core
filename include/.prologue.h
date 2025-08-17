#pragma once


// The library namespace definition.
#include ".bootstrap/namespace.h"

// Environment configuration.
#include ".bootstrap/constants.h"
#include ".bootstrap/macros.h"
#include ".bootstrap/configuration.h"

// Persistent external stuff.
#include ".bootstrap/persistent-std.h"
#include ".bootstrap/persistent-third-party.h"

// Conversion support for bootstrap constants.
#include ".bootstrap/internal/constants.h"
#include ".bootstrap/constants.converting.h"

// Logging basics.
#include ".global/logging/forwards.h"
#include ".global/logging/internal/constants.h"
#include ".global/logging/internal/functions.h"
#include ".global/logging/internal/BufferEncoder.h"
#include ".global/logging/internal/EncodedBuffer.h"
#include ".global/logging/internal/MessageLocation.h"
#include ".global/logging/internal/MessageChannel.h"
#include ".global/logging/internal/MessageFormat.h"
#include ".global/logging/LogMessage.h"
#include ".global/logging/macros.h"

// Most global stuff.
#include ".global/macros.h"

#include ".global/types/constants.h"
#include ".global/generic-functions/misc.h"
#include ".global/generic-functions/bytes.h"
#include ".global/generic-functions/chars.h"
#include ".global/generic-functions/memory.h"

#include ".global/types/generic-types.h"
#include ".global/types/generic-types.aliasing.h"
#include ".global/generic-functions/time.h"

#include ".global/stl/StandardArrayFacade.h"
#include ".global/stl/StandardDynamicArrayFacade.h"
#include ".global/stl/StandardForwardListFacade.h"
#include ".global/stl/StandardListFacade.h"

// Global types.
#include ".global/core-guidelines/NotNull.h"
#include ".global/types/internal/BasicPlainView.h"
#include ".global/types/PlainView.h"
#include ".global/types/internal/BasicPlainVector.h"
#include ".global/types/PlainVector.h"
#include ".global/types/RingBuffer.h"
#include ".global/types/DebugName.h"
#include ".global/types/ScopedPointer.h"
#include ".global/types/Hypothetical.forwards.h"
#include ".global/types/Hypothetical.internal.h"
#include ".global/types/internal/HypotheticalValue.h"
#include ".global/types/Hypothetical.h"

#include ".global/types/EnumFlags.struct.h"
#include ".global/types/EnumFlags.internal.h"
#include ".global/types/EnumFlags.h"

// First layer of platform-agnostic types. Cross-platform basic definitions.
#include ".global/functions.h"

// Second layer of platform-agnostic types. Platform-specific declarations.
#include ".global/platform/platform.h"

// Third layer of platform-agnostic types. Public platform-specific stuff.
// None here.

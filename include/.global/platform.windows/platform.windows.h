#pragma once


// External dependencies.
#include <windows.h>

// WinAPI macro moderation.
#include "drop-forbidden-macros.h"


namespace Black
{
inline namespace Core
{
inline namespace Global
{
// Microsoft Windows Desktop platform definitions.
inline namespace WindowsDesktop
{
// Internal platform-related stuff for Microsoft Windows Desktop platform.
namespace Internal
{

}
}
}
}
}


// Internal stuff.
#include "internal/ComObjectReleaser.h"

// Platform-specific stuff.
#include "functions.debug.windows.h"
#include "functions.formatting.windows.h"
#include "functions.memory.windows.h"

#include "functions.h"
#include "com-pointers.h"

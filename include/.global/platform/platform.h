#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Global
{
// Platform-specific definitions.
namespace Platform
{

}
}
}
}


// Forward declarations of platform-specific stuff.
#include "functions.debug.h"
#include "functions.formatting.h"
#include "functions.memory.h"

// Select the implementation of platform-specific code.
#if( BLACK_WINDOWS_DESKTOP_PLATFORM )
	#include "../platform.windows/platform.windows.h"
#elif( BLACK_MAC_OS_PLATFORM )
	#include "../platform.macos/platform.macos.h"
#elif( BLACK_LINUX_PLATFORM )
	#include "../platform.linux/platform.linux.h"
#elif( BLACK_ANDROID_PLATFORM )
	#include "../platform.android/platform.android.h"
#elif( BLACK_IOS_PLATFORM )
	#include "../platform.ios/platform.ios.h"
#else
	#error Current platform is unspecified or not defined
#endif

// Deferred implementations.

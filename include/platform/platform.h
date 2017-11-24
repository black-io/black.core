#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Platform
{}
}
}


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
#elif( BLACK_WINDOWS_MOBILE_PLATFORM )
	#include "../platform.winmo/platform.winmo.h"
#elif( BLACK_TIZEN_PLATFORM )
	#include "../platform.tizen/platform.tizen.h"
#else
	#error Current platform is unspecified or not defined
#endif
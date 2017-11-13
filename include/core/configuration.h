#pragma once


// Disable windows CRT `symbol deprecated` (C4996) warnings.
#if( !defined( _CRT_SECURE_NO_WARNINGS ) )
	#define _CRT_SECURE_NO_WARNINGS 1
#endif

// Build mode boolean flag stubs.
// This values may be used into `#if` checks.
#define BLACK_DEBUG_BUILD				0
#define BLACK_DRAFT_BUILD				0
#define BLACK_RELEASE_BUILD				0

// Target platform boolean flag stubs.
// This values may be used into `#if` checks.
#define BLACK_UNKNOWN_PLATFORM			0
#define BLACK_WINDOWS_DESKTOP_PLATFORM	0
#define BLACK_MAC_OS_PLATFORM			0
#define BLACK_LINUX_PLATFORM			0
#define BLACK_ANDROID_PLATFORM			0
#define BLACK_IOS_PLATFORM				0
#define BLACK_WINDOWS_MOBILE_PLATFORM	0

// Endianness boolean flag stubs.
// This values may be used into `#if` checks.
#define BLACK_BIG_ENDIAN				0
#define BLACK_LITTLE_ENDIAN				0
#define BLACK_PDP_ENDIAN				0

// Define some stuff depending on build configuration.
#if( defined( _DEBUG ) )
	// Force enable checked iterators if value not specified.
	#if( !defined( _SECURE_SCL ) && defined( _WIN32 ) )
		#define _SECURE_SCL	1
	#endif

	#include <stdlib.h>

	#undef BLACK_DEBUG_BUILD
	#define BLACK_DEBUG_BUILD	1
#elif( defined( _DRAFT_RELEASE ) )
	// Force disable checked iterators if value not specified.
	#if( !defined( _SECURE_SCL ) )
		#define _SECURE_SCL	0
	#endif

	#undef BLACK_DRAFT_BUILD
	#define BLACK_DRAFT_BUILD	1
#else
	// Force disable checked iterators if value not specified.
	#if( !defined( _SECURE_SCL ) )
		#define _SECURE_SCL	0
	#endif

	#undef BLACK_RELEASE_BUILD
	#define BLACK_RELEASE_BUILD	1
#endif

// Define some stuff depending on build platform.
#if( defined( _WIN32 ) )
	#undef BLACK_WINDOWS_DESKTOP_PLATFORM
	#define BLACK_WINDOWS_DESKTOP_PLATFORM	1

	#undef BLACK_LITTLE_ENDIAN
	#define BLACK_LITTLE_ENDIAN				1
#elif( defined( __MACOSX__ ) )
	#undef BLACK_MAC_OS_PLATFORM
	#define BLACK_MAC_OS_PLATFORM			1

	#undef BLACK_BIG_ENDIAN
	#define BLACK_BIG_ENDIAN				1
#elif( defined( __ANDROID__ ) )
	#undef BLACK_ANDROID_PLATFORM
	#define BLACK_ANDROID_PLATFORM			1

	#undef BLACK_LITTLE_ENDIAN
	#define BLACK_LITTLE_ENDIAN				1

	// Early access to `size_t` specification.
	#include <stddef.h>
#elif( defined( __iOS__ ) )
	#undef BLACK_IOS_PLATFORM
	#define BLACK_IOS_PLATFORM				1

	#undef BLACK_BIG_ENDIAN
	#define BLACK_BIG_ENDIAN				1
#else
	#error Current platform is unspecified or not defined.
#endif

// Detecting the exceptions enabled.
#if( defined( __EXCEPTIONS ) || defined( __cpp_exceptions ) )
	#define BLACK_EXCEPTIONS_ENABLED		1
#else
	#define BLACK_EXCEPTIONS_ENABLED		0
#endif

namespace Black
{
	// Declare current build mode.
	#if( BLACK_DEBUG_BUILD )
	constexpr BuildMode BUILD_CONFIGURATION	= BuildMode::Debug;
	#elif( BLACK_DRAFT_BUILD )
	constexpr BuildMode BUILD_CONFIGURATION	= BuildMode::Draft;
	#else
	constexpr BuildMode BUILD_CONFIGURATION	= BuildMode::Release;
	#endif

	// Declare current platform.
	#if( BLACK_WINDOWS_DESKTOP_PLATFORM )
	constexpr PlatformType BUILD_PLATFORM	= PlatformType::WindowsDesktop;
	#elif( BLACK_MAC_OS_PLATFORM )
	constexpr PlatformType BUILD_PLATFORM	= PlatformType::MacOs;
	#elif( BLACK_LINUX_PLATFORM )
	constexpr PlatformType BUILD_PLATFORM	= PlatformType::Linux;
	#elif( BLACK_ANDROID_PLATFORM )
	constexpr PlatformType BUILD_PLATFORM	= PlatformType::Android;
	#elif( BLACK_IOS_PLATFORM )
	constexpr PlatformType BUILD_PLATFORM	= PlatformType::Ios;
	#elif( BLACK_WINDOWS_MOBILE_PLATFORM )
	constexpr PlatformType BUILD_PLATFORM	= PlatformType::WindowsMobile;
	#else
		#error The `BUILD_PLATFORM` constant needs to be defined for current platform.
	#endif

	// Declare current platform endianness.
	#if( BLACK_LITTLE_ENDIAN )
	constexpr PlatformEndianness BUILD_ENDIANNESS	= PlatformEndianness::LittleEndian;
	#elif( BLACK_BIG_ENDIAN )
	constexpr PlatformEndianness BUILD_ENDIANNESS	= PlatformEndianness::BigEndian;
	#elif( BLACK_PDP_ENDIAN )
	constexpr PlatformEndianness BUILD_ENDIANNESS	= PlatformEndianness::PdpEndian;
	#else
		#error The `BUILD_ENDIANNESS` constatnt needs to be defined for curent platform.
	#endif
}

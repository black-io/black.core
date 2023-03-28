#pragma once


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

// Stub for name of target platform.
// Should not be used out of preprocessor stage.
#define BLACK_PLATFORM_NAME				unknown

// Endianness boolean flag stubs.
// This values may be used into `#if` checks.
#define BLACK_BIG_ENDIAN				0
#define BLACK_LITTLE_ENDIAN				0
#define BLACK_PDP_ENDIAN				0


// Define some stuff depending on build configuration.
#if( defined( _DEBUG ) )
	#undef BLACK_DEBUG_BUILD
	#define BLACK_DEBUG_BUILD	1
#elif( defined( _DRAFT_RELEASE ) )
	#undef BLACK_DRAFT_BUILD
	#define BLACK_DRAFT_BUILD	1
#else
	#undef BLACK_RELEASE_BUILD
	#define BLACK_RELEASE_BUILD	1
#endif


// Define some stuff depending on build platform.
#if( defined( _WIN32 ) )
	#undef BLACK_WINDOWS_DESKTOP_PLATFORM
	#define BLACK_WINDOWS_DESKTOP_PLATFORM	1

	#undef BLACK_PLATFORM_NAME
	#define BLACK_PLATFORM_NAME				windows
#elif( defined( __MACOSX__ ) )
	#undef BLACK_MAC_OS_PLATFORM
	#define BLACK_MAC_OS_PLATFORM			1

	#undef BLACK_PLATFORM_NAME
	#define BLACK_PLATFORM_NAME				macos
#elif( defined( __ANDROID__ ) )
	#undef BLACK_ANDROID_PLATFORM
	#define BLACK_ANDROID_PLATFORM			1

	#undef BLACK_PLATFORM_NAME
	#define BLACK_PLATFORM_NAME				android

	// Force JNI to use standard plain types.
	#define HAVE_INTTYPES_H					1

	// Early access to `size_t` definition.
	#include <stddef.h>
#elif( defined( __iOS__ ) )
	#undef BLACK_IOS_PLATFORM
	#define BLACK_IOS_PLATFORM				1

	#undef BLACK_PLATFORM_NAME
	#define BLACK_PLATFORM_NAME				ios
#else
	#error Current platform is unspecified or not defined.
#endif


// Detecting the system byte-order (endianness).
#if( defined( __LITTLE_ENDIAN__ ) )
	#undef BLACK_LITTLE_ENDIAN
	#define BLACK_LITTLE_ENDIAN			1
#elif( defined( __ARMEL__ ) || defined( __THUMBEL__ ) || defined( __AARCH64EL__ ) )
	#undef BLACK_LITTLE_ENDIAN
	#define BLACK_LITTLE_ENDIAN			1
#elif( defined( __MIPSEL__ ) || defined( _MIPSEL ) || defined( __MIPSEL ) )
	#undef BLACK_LITTLE_ENDIAN
	#define BLACK_LITTLE_ENDIAN			1
#elif( defined( __BIG_ENDIAN__ ) )
	#undef BLACK_BIG_ENDIAN
	#define BLACK_BIG_ENDIAN			1
#elif( defined( __ARMEB__ ) || defined( __THUMBEB__ ) || defined( __AARCH64EB__ ) )
	#undef BLACK_BIG_ENDIAN
	#define BLACK_BIG_ENDIAN			1
#elif( defined( __MIBSEB__ ) || defined( _MIBSEB ) || defined( __MIBSEB ) )
	#undef BLACK_BIG_ENDIAN
	#define BLACK_BIG_ENDIAN			1
#elif( defined( __BYTE_ORDER ) )
	#if( __BYTE_ORDER == __LITTLE_ENDIAN )
		#undef BLACK_LITTLE_ENDIAN
		#define BLACK_LITTLE_ENDIAN		1
	#elif( __BYTE_ORDER == __BIG_ENDIAN )
		#undef BLACK_BIG_ENDIAN
		#define BLACK_BIG_ENDIAN		1
	#endif
#elif( defined( __BYTE_ORDER__ ) )
	#if( __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ )
		#undef BLACK_LITTLE_ENDIAN
		#define BLACK_LITTLE_ENDIAN		1
	#elif( __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ )
		#undef BLACK_BIG_ENDIAN
		#define BLACK_BIG_ENDIAN		1
	#endif
#elif( defined( __FLOAT_WORD_ORDER__ ) )
	#if( __FLOAT_WORD_ORDER__ == __ORDER_LITTLE_ENDIAN__ )
		#undef BLACK_LITTLE_ENDIAN
		#define BLACK_LITTLE_ENDIAN		1
	#elif( __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__ )
		#undef BLACK_BIG_ENDIAN
		#define BLACK_BIG_ENDIAN		1
	#endif
#elif( BLACK_WINDOWS_DESKTOP_PLATFORM )
	#if( defined( _M_PPC ) )
		#undef BLACK_BIG_ENDIAN
		#define BLACK_BIG_ENDIAN		1
	#else
		#undef BLACK_LITTLE_ENDIAN
		#define BLACK_LITTLE_ENDIAN		1
	#endif
#else
	#error It's unable to detect the system byte-order (endianness).
#endif


// Detecting whether the exceptions enabled.
#if( defined( __cpp_exceptions ) || defined( __EXCEPTIONS ) )
	#define BLACK_EXCEPTIONS_ENABLED	1
#else
	#define BLACK_EXCEPTIONS_ENABLED	0
#endif


// Configure the common name of included platform-dependent code.
// This macro may be used in `#include` directive.
#define BLACK_CURRENT_PLATFORM_HEADER	BLACK_STRINGIFICATION( ../platform.BLACK_PLATFORM_NAME/platform.BLACK_PLATFORM_NAME.h )


namespace Black
{
	// Declare current build mode.
	#if( BLACK_DEBUG_BUILD )
	inline constexpr BuildMode BUILD_CONFIGURATION	= BuildMode::Debug;
	#elif( BLACK_DRAFT_BUILD )
	inline constexpr BuildMode BUILD_CONFIGURATION	= BuildMode::Draft;
	#elif( BLACK_RELEASE_BUILD )
	inline constexpr BuildMode BUILD_CONFIGURATION	= BuildMode::Release;
	#else
		#error The `BUILD_CONFIGURATION` constant needs to be defined for current platform.
	#endif

	// Declare current platform.
	#if( BLACK_WINDOWS_DESKTOP_PLATFORM )
	inline constexpr PlatformType BUILD_PLATFORM	= PlatformType::WindowsDesktop;
	#elif( BLACK_MAC_OS_PLATFORM )
	inline constexpr PlatformType BUILD_PLATFORM	= PlatformType::MacOs;
	#elif( BLACK_LINUX_PLATFORM )
	inline constexpr PlatformType BUILD_PLATFORM	= PlatformType::Linux;
	#elif( BLACK_ANDROID_PLATFORM )
	inline constexpr PlatformType BUILD_PLATFORM	= PlatformType::Android;
	#elif( BLACK_IOS_PLATFORM )
	inline constexpr PlatformType BUILD_PLATFORM	= PlatformType::Ios;
	#else
		#error The `BUILD_PLATFORM` constant needs to be defined for current platform.
	#endif

	// Declare current platform endianness.
	#if( BLACK_LITTLE_ENDIAN )
	inline constexpr PlatformEndianness BUILD_ENDIANNESS	= PlatformEndianness::LittleEndian;
	#elif( BLACK_BIG_ENDIAN )
	inline constexpr PlatformEndianness BUILD_ENDIANNESS	= PlatformEndianness::BigEndian;
	#elif( BLACK_PDP_ENDIAN )
	inline constexpr PlatformEndianness BUILD_ENDIANNESS	= PlatformEndianness::PdpEndian;
	#else
		#error The `BUILD_ENDIANNESS` constatnt needs to be defined for curent platform.
	#endif

	// Declare current exceptions support.
	inline constexpr bool USE_EXCEPTIONS = BLACK_EXCEPTIONS_ENABLED != 0;
}

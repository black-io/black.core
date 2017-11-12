#pragma once


// Regular 'conditional return' statement.
#define CRET( CONDITION, ... )	if( CONDITION ) { return __VA_ARGS__; }

// Regular 'conditional continue' statement.
#define CCON( CONDITION )		if( CONDITION ) { continue; }

// Regular 'conditional break' statement.
#define CBRK( CONDITION )		if( CONDITION ) { break; }


// Regular 'in-code breakpoint' statement.
#if( !BLACK_RELEASE_BUILD )
	#if( BLACK_WINDOWS_DESKTOP_PLATFORM )
		#define BLACK_DEBUG_BREAK( ... )	__debugbreak()
	#elif( BLACK_MAC_OS_PLATFORM )
		#define BLACK_DEBUG_BREAK( ... )	__asm__( "int $3" )
	#elif( BLACK_ANDROID_PLATFORM )
		#define BLACK_DEBUG_BREAK( ... )	__builtin_trap()
	#elif( BLACK_IOS_PLATFORM )
		#define BLACK_DEBUG_BREAK( ... )	__builtin_trap()
	#endif
#else
	#define BLACK_DEBUG_BREAK( ... )
#endif

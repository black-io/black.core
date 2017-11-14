#pragma once


// Regular 'conditional return' statement.
#define CRET( CONDITION, ... )	if( CONDITION ) { return __VA_ARGS__; }

// Regular 'conditional continue' statement.
#define CCON( CONDITION )		if( CONDITION ) { continue; }

// Regular 'conditional break' statement.
#define CBRK( CONDITION )		if( CONDITION ) { break; }


// Regular 'debug-only' code statement.
#if( BLACK_RELEASE_BUILD )
	#define BLACK_NON_RELEASE_CODE( ... )
#else
	#define BLACK_NON_RELEASE_CODE( ... )	__VA_ARGS__
#endif


// Regular 'in-code breakpoint' statement.
#if( BLACK_RELEASE_BUILD )
	#define BLACK_DEBUG_BREAK( ... )
#else
	#if( BLACK_WINDOWS_DESKTOP_PLATFORM )
		#define BLACK_DEBUG_BREAK( ... )	__debugbreak()
	#elif( BLACK_MAC_OS_PLATFORM )
		#define BLACK_DEBUG_BREAK( ... )	__asm__( "int $3" )
	#elif( BLACK_ANDROID_PLATFORM )
		#define BLACK_DEBUG_BREAK( ... )	__builtin_trap()
	#elif( BLACK_IOS_PLATFORM )
		#define BLACK_DEBUG_BREAK( ... )	__builtin_trap()
	#endif
#endif


// Regular 'in-code manual failure' statement.
#if( BLACK_EXCEPTIONS_ENABLED )
	#define BLACK_RUNTIME_FAILURE( ... )	std::runtime_error{ __VA_ARGS__ }
#else
	#define BLACK_RUNTIME_FAILURE( ... )	std::abort()
#endif


// Regular 'assume' statement.
#if( BLACK_WINDOWS_DESKTOP_PLATFORM || BLACK_WINDOWS_MOBILE_PLATFORM )
	#define BLACK_ASSUME( ... )	__assume( __VA_ARGS__ )
#else
	#define BLACK_ASSUME( ... )
#endif


// Shunting the logging subsystem by default.
#if( !defined( BLACK_LOG_CRITICAL ) )
	#define BLACK_LOG_CRITICAL( ... )
#endif

#if( !defined( BLACK_LOGS_CLOSE ) )
	#define BLACK_LOGS_CLOSE( ... )
#endif


// Code logics separation macros.
#define BLACK_STRING_MACRO( EXPRESSION )	#EXPRESSION
#define BLACK_STRINGIFICATION( EXPRESSION )	BLACK_STRING_MACRO( EXPRESSION )


// Regular expectation and insurance.
#define EXPECTS( ... )																								\
if( !( __VA_ARGS__ ) )																								\
{																													\
	BLACK_LOG_CRITICAL( "Black", "Unexpected result of `" BLACK_STRINGIFICATION( __VA_ARGS__ ) "` expression." );	\
	BLACK_LOGS_CLOSE();																								\
	BLACK_DEBUG_BREAK();																							\
	BLACK_RUNTIME_FAILURE( BLACK_STRINGIFICATION( __VA_ARGS__ ) " failed." );										\
}

#define ENSURES( ... )																								\
if( !( __VA_ARGS__ ) )																								\
{																													\
	BLACK_LOG_CRITICAL( "Black", "Unexpected result of `" BLACK_STRINGIFICATION( __VA_ARGS__ ) "` expression." );	\
	BLACK_LOGS_CLOSE();																								\
	BLACK_DEBUG_BREAK();																							\
	BLACK_RUNTIME_FAILURE( BLACK_STRINGIFICATION( __VA_ARGS__ ) " failed." );										\
}


#if( BLACK_RELEASE_BUILD )
	#define EXPECTS_DEBUG( ... )
	#define ENSURES_DEBUG( ... )
#else
	#define EXPECTS_DEBUG( ... )	EXPECTS( __VA_ARGS__ )
	#define ENSURES_DEBUG( ... )	ENSURES( __VA_ARGS__ )
#endif

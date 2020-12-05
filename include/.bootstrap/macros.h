#pragma once


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


// Regular 'assume' statement.
#if( BLACK_WINDOWS_DESKTOP_PLATFORM || BLACK_WINDOWS_MOBILE_PLATFORM )
	#define BLACK_ASSUME( ... )	__assume( __VA_ARGS__ )
#else
	#define BLACK_ASSUME( ... )
#endif


// Regular SFINAE statement for function templates.
#define BLACK_SFINAE( CONDITION )	char (*)[ CONDITION ] = 0


// Shunting the logging subsystem by default.
#if( !defined( BLACK_LOG_CRITICAL ) )
	#define BLACK_LOG_CRITICAL( ... )
#endif

#if( !defined( BLACK_LOG_ERROR ) )
	#define BLACK_LOG_ERROR( ... )
#endif

#if( !defined( BLACK_LOG_WARNING ) )
	#define BLACK_LOG_WARNING( ... )
#endif

#if( !defined( BLACK_LOG_DEBUG ) )
	#define BLACK_LOG_DEBUG( ... )
#endif

#if( !defined( BLACK_LOGS_CLOSE ) )
	#define BLACK_LOGS_CLOSE( ... )
#endif


// Regular 'conditional return' statement.
#define CRET( CONDITION, ... )								{ if( CONDITION ) { return __VA_ARGS__; } }

// Regular 'conditional continue' statement.
#define CCON( CONDITION )									{ if( CONDITION ) { continue; } }

// Regular 'conditional break' statement.
#define CBRK( CONDITION )									{ if( CONDITION ) { break; } }

// 'conditional return' statement with error reporting.
#define CRETE( CONDITION, RESULT, CHANNEL, FORMAT, ... )	{ if( CONDITION ){ BLACK_LOG_ERROR( CHANNEL, FORMAT, ##__VA_ARGS__ ); return RESULT; } }

// 'conditional continue' statement with error reporting.
#define CCONE( CONDITION, CHANNEL, FORMAT, ... )			{ if( CONDITION ){ BLACK_LOG_ERROR( CHANNEL, FORMAT, ##__VA_ARGS__ ); continue; } }

// 'conditional break' statement with error reporting.
#define CBRKE( CONDITION, CHANNEL, FORMAT, ... )			{ if( CONDITION ){ BLACK_LOG_ERROR( CHANNEL, FORMAT, ##__VA_ARGS__ ); break; } }

// 'conditional return' statement with warning reporting.
#define CRETW( CONDITION, RESULT, CHANNEL, FORMAT, ... )	{ if( CONDITION ){ BLACK_LOG_WARNING( CHANNEL, FORMAT, ##__VA_ARGS__ ); return RESULT; } }

// 'conditional continue' statement with warning reporting.
#define CCONW( CONDITION, CHANNEL, FORMAT, ... )			{ if( CONDITION ){ BLACK_LOG_WARNING( CHANNEL, FORMAT, ##__VA_ARGS__ ); continue; } }

// 'conditional break' statement with warning reporting.
#define CBRKW( CONDITION, CHANNEL, FORMAT, ... )			{ if( CONDITION ){ BLACK_LOG_WARNING( CHANNEL, FORMAT, ##__VA_ARGS__ ); break; } }


// String from arbitrary expression.
#define BLACK_STRING_MACRO( EXPRESSION )	#EXPRESSION
#define BLACK_STRINGIFICATION( EXPRESSION )	BLACK_STRING_MACRO( EXPRESSION )


// Regular expectation.
#define EXPECTS( ... )																									\
{																														\
	if( !( __VA_ARGS__ ) ) [[unlikely]]																					\
	{																													\
		BLACK_LOG_CRITICAL( "Black", "Unexpected result of `" BLACK_STRINGIFICATION( __VA_ARGS__ ) "` expression." );	\
		BLACK_LOGS_CLOSE();																								\
		BLACK_DEBUG_BREAK();																							\
		std::abort();																									\
	}																													\
}

// Regular insurance.
#define ENSURES( ... )																									\
{																														\
	if( !( __VA_ARGS__ ) ) [[unlikely]]																					\
	{																													\
		BLACK_LOG_CRITICAL( "Black", "Unexpected result of `" BLACK_STRINGIFICATION( __VA_ARGS__ ) "` expression." );	\
		BLACK_LOGS_CLOSE();																								\
		BLACK_DEBUG_BREAK();																							\
		std::abort();																									\
	}																													\
}


#if( BLACK_RELEASE_BUILD )
	#define CRETD( CONDITION, RESULT, CHANNEL, FORMAT, ... )	CRET( CONDITION, RESULT )
	#define CCOND( CONDITION, CHANNEL, FORMAT, ... )			CCON( CONDITION )
	#define CBRKD( CONDITION, CHANNEL, FORMAT, ... )			CBRK( CONDITION )

	#define EXPECTS_DEBUG( ... )
	#define ENSURES_DEBUG( ... )
#else
	#define CRETD( CONDITION, RESULT, CHANNEL, FORMAT, ... )	{ if( CONDITION ){ BLACK_LOG_DEBUG( CHANNEL, FORMAT, ##__VA_ARGS__ ); return RESULT; } }
	#define CCOND( CONDITION, CHANNEL, FORMAT, ... )			{ if( CONDITION ){ BLACK_LOG_DEBUG( CHANNEL, FORMAT, ##__VA_ARGS__ ); continue; } }
	#define CBRKD( CONDITION, CHANNEL, FORMAT, ... )			{ if( CONDITION ){ BLACK_LOG_DEBUG( CHANNEL, FORMAT, ##__VA_ARGS__ ); break; } }

	#define EXPECTS_DEBUG( ... )								EXPECTS( __VA_ARGS__ )
	#define ENSURES_DEBUG( ... )								ENSURES( __VA_ARGS__ )
#endif

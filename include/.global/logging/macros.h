#pragma once


// Shunting the externally defined logging, if exist.
#if( defined( BLACK_LOG_FATAL ) )
	#undef BLACK_LOG_FATAL
#endif

#if( defined( BLACK_LOG_CRITICAL ) )
	#undef BLACK_LOG_CRITICAL
#endif

#if( defined( BLACK_LOG_ERROR ) )
	#undef BLACK_LOG_ERROR
#endif

#if( defined( BLACK_LOG_WARNING ) )
	#undef BLACK_LOG_WARNING
#endif

#if( defined( BLACK_LOG_INFO ) )
	#undef BLACK_LOG_INFO
#endif

#if( defined( BLACK_LOG_VERBOSE ) )
	#undef BLACK_LOG_VERBOSE
#endif

#if( defined( BLACK_LOG_DEBUG ) )
	#undef BLACK_LOG_DEBUG
#endif

#if( defined( BLACK_LOGS_CLOSE ) )
	#undef BLACK_LOGS_CLOSE
#endif


// Regular logging macro.
#define BLACK_DEFINE_LOGGING_SECTION( CATEGORY, CHANNEL, FORMAT, FUNCTION, FILE, LINE, ... )																\
{																																							\
	static const Black::LogMessage::EncodedString<std::char_traits<char>::length( FUNCTION )>	logging_function_name{ FUNCTION };							\
	static const Black::LogMessage::EncodedString<std::char_traits<char>::length( FILE )>		logging_file_path{ FILE };									\
	static const Black::LogMessage::EncodedString<std::char_traits<char>::length( CHANNEL )>	logging_log_channel{ CHANNEL };								\
	static const Black::LogMessage::EncodedString<std::char_traits<char>::length( FORMAT )>		logging_format{ FORMAT };									\
																																							\
	static const Black::LogMessage logging_message{ CATEGORY, *logging_function_name, *logging_file_path, LINE, *logging_log_channel, *logging_format };	\
	logging_message.Send( __VA_ARGS__ );																													\
}

// Build configuration dependent logging macro.
#if( BLACK_RELEASE_BUILD )
	#define BLACK_DEFINE_NONRELEASE_LOGGING_SECTION( ... )
#else
	#define BLACK_DEFINE_NONRELEASE_LOGGING_SECTION BLACK_DEFINE_LOGGING_SECTION
#endif


// Shunting the logging subsystem by default.
#define BLACK_LOG_FATAL( CHANNEL, FORMAT, ... ) \
BLACK_DEFINE_LOGGING_SECTION( Black::LogMessage::Category::Fatal, CHANNEL, FORMAT, __FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__ )

#define BLACK_LOG_CRITICAL( CHANNEL, FORMAT, ... ) \
BLACK_DEFINE_LOGGING_SECTION( Black::LogMessage::Category::Critical, CHANNEL, FORMAT, __FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__ )

#define BLACK_LOG_ERROR( CHANNEL, FORMAT, ... ) \
BLACK_DEFINE_LOGGING_SECTION( Black::LogMessage::Category::Error, CHANNEL, FORMAT, __FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__ )

#define BLACK_LOG_WARNING( CHANNEL, FORMAT, ... ) \
BLACK_DEFINE_LOGGING_SECTION( Black::LogMessage::Category::Warning, CHANNEL, FORMAT, __FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__ )

#define BLACK_LOG_INFO( CHANNEL, FORMAT, ... ) \
BLACK_DEFINE_NONRELEASE_LOGGING_SECTION( Black::LogMessage::Category::Info, CHANNEL, FORMAT, __FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__ )

#define BLACK_LOG_VERBOSE( CHANNEL, FORMAT, ... ) \
BLACK_DEFINE_NONRELEASE_LOGGING_SECTION( Black::LogMessage::Category::Verbose, CHANNEL, FORMAT, __FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__ )

#define BLACK_LOG_DEBUG( CHANNEL, FORMAT, ... ) \
BLACK_DEFINE_NONRELEASE_LOGGING_SECTION( Black::LogMessage::Category::Debug, CHANNEL, FORMAT, __FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__ )

#define BLACK_LOGS_CLOSE( ... ) \
Black::LogMessage::CloseLogs()

#include <black/core.h>
#include <black/core/algorithms.h>


namespace
{
	const android_LogPriority TranslateLogCategory( const Black::LogMessage::Category category )
	{
		switch( category )
		{
			case Black::LogMessage::Category::Fatal:	return ANDROID_LOG_FATAL;
			case Black::LogMessage::Category::Critical:	return ANDROID_LOG_ERROR;
			case Black::LogMessage::Category::Error:	return ANDROID_LOG_ERROR;
			case Black::LogMessage::Category::Warning:	return ANDROID_LOG_WARN;
			case Black::LogMessage::Category::Info:		return ANDROID_LOG_INFO;
			case Black::LogMessage::Category::Verbose:	return ANDROID_LOG_VERBOSE;
			case Black::LogMessage::Category::Debug:	return ANDROID_LOG_DEBUG;
		}

		return ANDROID_LOG_UNKNOWN;
	}
}


namespace Black
{
inline namespace Core
{
inline namespace Platform
{
inline namespace PlatformSpecific
{
	void SendDebugString( std::string_view content )
	{
		if constexpr( Black::BUILD_CONFIGURATION == Black::BuildMode::Debug )
		{
			const size_t content_length = content.size();
			char* const string_buffer	= static_cast<char*>( alloca( content_length + 1 ) );

			CopyMemory( string_buffer, content.data(), content_length );
			string_buffer[ content_length ] = 0;

			__android_log_write( ANDROID_LOG_DEBUG, "Black/Debugging", string_buffer );
		}
	}

	void SendDebuggerMessage( const Black::LogMessage& message, std::string&& content )
	{
		if constexpr( Black::BUILD_CONFIGURATION == Black::BuildMode::Debug )
		{
			std::string buffer;

			if( !message.GetFilePath().empty() )
			{
				buffer = Black::FormatString(
					"{} ({}): - {}\n",
					message.GetFilePath(),
					message.GetFileLine(),
					content
				);
			}
			else
			{
				buffer = std::move( content );
			}

			// There is not zero termination in channel buffer.
			const size_t channel_size = message.GetChannel().size();
			char* log_tag = static_cast<char*>( alloca( channel_size + 1 ) );
			Black::CopyMemory( log_tag, message.GetChannel().data(), channel_size );
			log_tag[ channel_size ] = 0;

			const android_LogPriority priority = ::TranslateLogCategory( message.GetCategory() );
			__android_log_write( priority, log_tag, content.data() );
		}
	}
}
}
}
}

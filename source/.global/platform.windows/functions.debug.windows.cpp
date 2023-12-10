#include <black/core.h>
#include <black/core/algorithms.h>


namespace
{
	std::string_view GetLogCategoryName( const Black::LogMessage::Category category )
	{
		switch( category )
		{
			case Black::LogMessage::Category::Fatal:	return "FATL";
			case Black::LogMessage::Category::Critical:	return "CRIT";
			case Black::LogMessage::Category::Error:	return "EROR";
			case Black::LogMessage::Category::Warning:	return "WARN";
			case Black::LogMessage::Category::Info:		return "INFO";
			case Black::LogMessage::Category::Verbose:	return "VERB";
			case Black::LogMessage::Category::Debug:	return "DBUG";
		}

		return "????";
	}
}


namespace Black
{
inline namespace Core
{
inline namespace Global
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
			char* const string_buffer	= static_cast<char*>( _malloca( content_length + 2 ) );
			CRET( string_buffer == nullptr );

			auto buffer_cleaner = Black::ScopeLeaveHandler{ [string_buffer]() { _freea( string_buffer ); } };

			CopyMemory( string_buffer, content.data(), content_length );
			string_buffer[ content_length ]		= '\n';
			string_buffer[ content_length + 1 ]	= 0;

			::OutputDebugStringA( string_buffer );
		}
	}

	void SendDebuggerMessage( const Black::LogMessage& message, std::string&& content )
	{
		if constexpr( Black::BUILD_CONFIGURATION == Black::BuildMode::Debug )
		{
			std::string buffer;

			if( message.GetFilePath().empty() )
			{
				buffer = Black::FormatString(
					"[{}|{}]\t- {}\n",
					::GetLogCategoryName( message.GetCategory() ),
					message.GetChannel(),
					content
				);
			}
			else
			{
				buffer = Black::FormatString(
					"{} ({}): [{}|{}]\t- {}\n",
					message.GetFilePath(),
					message.GetFileLine(),
					::GetLogCategoryName( message.GetCategory() ),
					message.GetChannel(),
					content
				);
			}

			::OutputDebugStringA( buffer.data() );
		}
	}
}
}
}
}
}

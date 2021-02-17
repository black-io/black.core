#include <black/core.h>


namespace Black
{
inline namespace Core
{
inline namespace Global
{
inline namespace Logging
{
namespace Internal
{
	void CloseLogs()
	{
	}

	const MessageId GetMessageUniqueId()
	{
		return {};
	}

	const LocationId GetLocationUniqueId( std::string_view function_name, std::string_view file_path, const size_t file_line )
	{
		return {};
	}

	const ChannelId GetChannelUniqueId( std::string_view log_channel )
	{
		return {};
	}

	const FormatId GetFormatUniqueId( std::string_view format )
	{
		return {};
	}

	const bool IsMessageEnabled( const MessageId message_id )
	{
		return false;
	}

	std::string_view GetFunctionName( const LocationId location_id )
	{
		return {};
	}

	std::string_view GetFilePath( const LocationId location_id )
	{
		return {};
	}

	const size_t GetFileLine( const LocationId location_id )
	{
		return 0;
	}

	const bool IsChannelEnabled( const ChannelId channel_id )
	{
		return false;
	}

	std::string_view GetChannel( const ChannelId channel_id )
	{
		return {};
	}

	std::string_view GetFormat( const FormatId format_id )
	{
		return {};
	}
}
}
}
}
}

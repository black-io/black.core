#include <black/core.h>

#include "LogMessageRegistry.h"
#include "MessageLocationRegistry.h"
#include "MessageChannelRegistry.h"
#include "MessageFormatRegistry.h"


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
	const MessageId GetMessageUniqueId( const Black::LogMessage& message )
	{
		return MessageId{ ::LogMessageRegistry::GetUniqueId( message ) };
	}

	const LocationId GetLocationUniqueId( std::string_view function_name, std::string_view file_path, const size_t file_line )
	{
		return LocationId{ ::MessageLocationRegistry::GetUniqueId( function_name, file_path, file_line ) };
	}

	const ChannelId GetChannelUniqueId( std::string_view log_channel )
	{
		return ChannelId{ ::MessageChannelRegistry::GetUniqueId( log_channel ) };
	}

	const FormatId GetFormatUniqueId( std::string_view format )
	{
		return FormatId{ ::MessageFormatRegistry::GetUniqueId( format ) };
	}

	const bool IsMessageEnabled( const MessageId message_id )
	{
		return ::LogMessageRegistry::IsMessageEnabled( Black::GetEnumValue( message_id ) );
	}

	std::string_view GetFunctionName( const LocationId location_id )
	{
		return ::MessageLocationRegistry::GetFunctionName( Black::GetEnumValue( location_id ) );
	}

	std::string_view GetFilePath( const LocationId location_id )
	{
		return ::MessageLocationRegistry::GetFilePath( Black::GetEnumValue( location_id ) );
	}

	const size_t GetFileLine( const LocationId location_id )
	{
		return ::MessageLocationRegistry::GetFileLine( Black::GetEnumValue( location_id ) );
	}

	const bool IsChannelEnabled( const ChannelId channel_id )
	{
		return ::MessageChannelRegistry::IsChannelEnabled( Black::GetEnumValue( channel_id ) );
	}

	std::string_view GetChannel( const ChannelId channel_id )
	{
		return ::MessageChannelRegistry::GetChannel( Black::GetEnumValue( channel_id ) );
	}

	std::string_view GetFormat( const FormatId format_id )
	{
		return ::MessageFormatRegistry::GetFormat( Black::GetEnumValue( format_id ) );
	}
}
}
}
}
}

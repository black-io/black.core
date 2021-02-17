#pragma once


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
	//
	void CloseLogs();

	//
	const MessageId GetMessageUniqueId();

	//
	const LocationId GetLocationUniqueId( std::string_view function_name, std::string_view file_path, const size_t file_line );

	//
	const ChannelId GetChannelUniqueId( std::string_view log_channel );

	//
	const FormatId GetFormatUniqueId( std::string_view format );

	//
	const bool IsMessageEnabled( const MessageId message_id );

	//
	std::string_view GetFunctionName( const LocationId location_id );

	//
	std::string_view GetFilePath( const LocationId location_id );

	//
	const size_t GetFileLine( const LocationId location_id );

	//
	const bool IsChannelEnabled( const ChannelId channel_id );

	//
	std::string_view GetChannel( const ChannelId channel_id );

	//
	std::string_view GetFormat( const FormatId format_id );
}
}
}
}
}

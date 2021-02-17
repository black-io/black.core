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
	class MessageRegistry final
	{
	// Public static interface.
	public:
		//
		static void Close();


		//
		static const MessageId GetMessageUniqueId();

		//
		static const LocationId GetLocationId( std::string_view function_name, std::string_view file_path, const size_t file_line );

		//
		static const ChannelId GetChannelId( std::string_view log_channel );

		//
		static const FormatId GetFormatId( std::string_view format );


		//
		static const bool IsMessageEnabled( const MessageId message_id );


		//
		static std::string_view GetFunctionName( const LocationId location_id );

		//
		static std::string_view GetFilePath( const LocationId location_id );

		//
		static const size_t GetFileLine( const LocationId location_id );


		//
		static const bool IsChannelEnabled( const ChannelId channel_id );

		//
		static std::string_view GetChannel( const ChannelId channel_id );


		//
		static std::string_view GetFormat( const FormatId format_id );


	// Construction and initialization.
	public:
		MessageRegistry()							= default;
		MessageRegistry( const MessageRegistry& )	= delete;
		MessageRegistry( MessageRegistry&& )		= delete;


		MessageRegistry& operator = ( const MessageRegistry& )	= delete;
		MessageRegistry& operator = ( MessageRegistry&& )		= delete;
	};
}
}
}
}
}

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
		static const MessageId GetMessageUniqueId();

		//
		static const LocationId GetLocationId( std::string_view function_name, std::string_view file_path, const size_t file_line );

		//
		static std::string_view GetFunctionName( const LocationId location_id );

		//
		static std::string_view GetFilePath( const LocationId location_id );

		//
		static const size_t GetFileLine( const LocationId location_id );


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

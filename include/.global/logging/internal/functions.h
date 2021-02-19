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
	/**
		@brief	Get the unique ID for given log message.

		From this point the given message at any time may identified by returned ID.
		The function is thread-safe and freely can be used in multiple threads in cost of synchronization.

		@param	message	The message to provide unique ID.
		@return			The value returned is the ID of given message.
	*/
	const MessageId GetMessageUniqueId( const Black::LogMessage& message );

	/**
		@brief	Get the unique ID for given logging point location.

		All given arguments are considered as unique logging location and the unique ID emitted as result for it.
		From this point the given location at any time may be identified by returned ID.
		The function is thread-safe and freely can be used in multiple threads in cost of synchronization.

		@param	function_name	Name of the function where the logging point occurs.
		@param	file_path		Source code file path, where the logging point defined.
		@param	file_line		Source code line number of logging point.
		@return					The value returned is the ID of given location.
	*/
	const LocationId GetLocationUniqueId( std::string_view function_name, std::string_view file_path, const size_t file_line );

	/**
		@brief	Get the unique ID for given log channel.

		From this point the given channel at any time may be identified by returned ID.
		The function is thread-safe and freely can be used in multiple threads in cost of synchronization.

		@param	log_channel		Logging channel.
	*/
	const ChannelId GetChannelUniqueId( std::string_view log_channel );

	/**
		@brief	Get the unique ID for given log format.

		From this point the given format at any time may be identified by returned ID.
		The function is thread-safe and freely can be used in multiple threads in cost of synchronization.

		@param	log_channel		Format of log message.
	*/
	const FormatId GetFormatUniqueId( std::string_view format );

	/**
		@brief	Whether the message is enabled and may appear in logs.

		The `message_id` should be one of valid values that obtained via `GetMessageUniqueId` function.
		The function is thread-safe and freely can be used in multiple threads in cost of synchronization.

		@param	message_id	Unique ID of message.
		@return				`true` for enabled message and `false` for other.
		@retval	false		For any given invalid ID.
	*/
	const bool IsMessageEnabled( const MessageId message_id );

	/**
		@brief	Get the name of function, where the logging location with given ID occurs.

		The `location_id` should be one of valid values that obtained via `GetLocationUniqueId` function.
		The function is thread-safe and freely can be used in multiple threads in cost of synchronization.

		@param	location_id	Unique ID of logging location.
		@return				The value returned is the valid name of function corresponded to given location ID.
		@retval	""			Empty string view will be returned for any given invalid ID.
	*/
	std::string_view GetFunctionName( const LocationId location_id );

	/**
		@brief	Get the source code file path, where the logging location with given ID occurs.

		The `location_id` should be one of valid values that obtained via `GetLocationUniqueId` function.
		The function is thread-safe and freely can be used in multiple threads in cost of synchronization.

		@param	location_id	Unique ID of logging location.
		@return				The value returned is the source code file path corresponded to given location ID.
		@retval	""			Empty string view will be returned for any given invalid ID.
	*/
	std::string_view GetFilePath( const LocationId location_id );

	/**
		@brief	Get the source code line number for the logging location with given ID.

		The `location_id` should be one of valid values that obtained via `GetLocationUniqueId` function.
		The function is thread-safe and freely can be used in multiple threads in cost of synchronization.

		@param	location_id	Unique ID of logging location.
		@return				The value returned is valid number of source code line of logging location.
		@retval	0			For any given invalid ID.
	*/
	const size_t GetFileLine( const LocationId location_id );

	/**
		@brief	Whether the logging channel is enabled for logging.

		The `channel_id` should be one of valid values that obtained via `GetChannelUniqueId` function.
		The function is thread-safe and freely can be used in multiple threads in cost of synchronization.

		@param	channel_id	Unique ID of logging channel.
		@return				`true` if channel is allowed for logging and `false` in other cases.
		@retval	false		For any given invalid ID.
	*/
	const bool IsChannelEnabled( const ChannelId channel_id );

	/**
		@brief	Get the logging channel by given ID.

		The `channel_id` should be one of valid values that obtained via `GetChannelUniqueId` function.
		The function is thread-safe and freely can be used in multiple threads in cost of synchronization.

		@param	channel_id	Unique ID of logging channel.
		@return				The value returned is the channel corresponded to given ID.
		@retval	""			Empty string view will be returned for any given invalid ID.
	*/
	std::string_view GetChannel( const ChannelId channel_id );

	/**
		@brief	Get the log format by given ID.

		The `format_id` should be one of valid values that obtained via `GetFormatUniqueId` function.
		The function is thread-safe and freely can be used in multiple threads in cost of synchronization.

		@param	format_id	Unique ID of log format.
		@return				The value returned is the format corresponded to given ID.
		@retval	""			Empty string view will be returned for any given invalid ID.
	*/
	std::string_view GetFormat( const FormatId format_id );
}
}
}
}
}

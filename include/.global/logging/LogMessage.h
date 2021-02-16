#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Global
{
inline namespace Logging
{
	/**
		@brief	Logging message.

		The type implements the entry point into logging subsystem. It represents the message at some point of program.
		The message is designed in sight of high performance on logging and as low memory consumption, as possible for my skills.

		One should never went into necessary of manually manage the logging messages. Instead of it, the corresponded logging macros should be used.
		It's much easier to use logging via `BLACK_LOG_*` macros. Just place it at the function you desire to log and all will be done on program translation.
	*/
	class LogMessage final
	{
	// Public inner types.
	public:
		// Message unique id.
		using Id = Internal::MessageId;

		// Message category.
		using Category = Internal::MessageCategory;

		// Encoded buffer for string literals, such as source code file path or channel.
		template< size_t LENGTH >
		using EncodedString = Internal::EncodedBuffer<LENGTH>;

	// Construction and initialization.
	public:
		LogMessage()					= delete;
		LogMessage( const LogMessage& )	= delete;
		LogMessage( LogMessage&& )		= delete;

		inline LogMessage(
			const Category category,
			std::string_view function_name,
			std::string_view file_path,
			const size_t file_line,
			std::string_view log_channel,
			std::string_view format
		);


		LogMessage& operator = ( const LogMessage& )	= delete;
		LogMessage& operator = ( LogMessage&& )			= delete;

	// Public static interface.
	public:
		// Close the logging session.
		static void CloseLogs();

	// Public interface.
	public:
		//
		template< typename... TArguments >
		inline void Send( TArguments&&... arguments ) const;


		// Whether the message is able to be sent.
		const bool IsEnabled() const;


		// get the unique identifier of message.
		inline const Id GetId() const				{ return m_id; };

		// Get the category of message.
		inline const Category GetCategory() const	{ return m_category; };

	// Private state.
	private:
		const Id					m_id;			// Unique identifier of message.
		const Internal::LocationId	m_location_id;	// Unique identifier of source code location.
		const Internal::ChannelId	m_channel_id;	// Unique identifier of logging channel.
		const Internal::FormatId	m_format_id;	// Unique identifier of message format.
		const Category				m_category;		// Message category.
	};
}
}
}
}
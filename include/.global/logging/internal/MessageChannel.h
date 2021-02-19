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
		@brief	Logging message channel adapter.

		The channel of log messages is required to be uniquely identified in the logging core.
		This adapter is used for purposes of such registration. In addition, the adapter implements the assess to registered data via given unique ID.

		The logging message channel represents the path of some virtual file system, where the last name represents the name of log file to write,
		and other names are the folder names.
		The couple of logging channels may represent the structure of logging filesystem, where the most leaf channels are the sub-channels for the most root ones.
		Any logging channel is able to be disabled. In disabled state the channel and all its sub-channels are unable to transfer the log entries.

		@tparam	BUILD_CONFIGURATION	Build configuration to specify the functionality of adapter.
	*/
	template< Black::BuildMode BUILD_CONFIGURATION >
	class MessageChannel final
	{
	// Construction and initialization.
	public:
		inline MessageChannel( std::string_view log_channel );

	// Public interface.
	public:
		/// @brief	Whether the channel is enabled.
		inline const bool IsEnabled() const;


		/// @brief	Get the encoded string of logging channel.
		inline std::string_view GetRawChannel() const;

		/// @brief	Get the decoded (original) string of logging channel.
		inline std::string GetChannel() const;


		/// @brief	Get the unique ID of channel.
		inline const ChannelId GetId() const		{ return m_id; };


		inline const ChannelId operator * () const	{ return m_id; };

	// Private state.
	private:
		const ChannelId m_id; // Unique id for hosted logging channel.
	};

	// The selection variant for Debug build configuration. It includes some additional fields.
	template<>
	class MessageChannel<Black::BuildMode::Debug> final
	{
	// Construction and initialization.
	public:
		inline MessageChannel( std::string_view log_channel );

	// Public interface.
	public:
		/// @brief	Whether the channel is enabled.
		inline const bool IsEnabled() const;


		/// @brief	Get the encoded string of logging channel.
		inline std::string_view GetRawChannel() const	{ return m_channel; };

		/// @brief	Get the decoded (original) string of logging channel.
		inline std::string GetChannel() const			{ return BufferEncoder::Decode( std::string{ m_channel } ); };


		/// @brief	Get the unique ID of channel.
		inline const ChannelId GetId() const			{ return m_id; };


		inline const ChannelId operator * () const		{ return m_id; };

	// Private state.
	private:
		const std::string_view	m_channel;	// Hosted logging channel.
		const ChannelId			m_id;		// Unique id for hosted logging channel.
	};
}
}
}
}
}

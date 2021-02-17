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
	template< Black::BuildMode BUILD_CONFIGURATION >
	class MessageChannel final
	{
	// Construction and initialization.
	public:
		inline MessageChannel( std::string_view log_channel );

	// Public interface.
	public:
		//
		inline const bool IsEnabled() const;


		//
		inline std::string_view GetRawChannel() const;

		//
		inline std::string GetChannel() const;


		//
		inline const ChannelId GetId() const		{ return m_id; };


		inline const ChannelId operator * () const	{ return m_id; };

	// Private state.
	private:
		const ChannelId m_id; // Unique id for hosted logging channel.
	};

	//
	template<>
	class MessageChannel<Black::BuildMode::Debug> final
	{
	// Construction and initialization.
	public:
		inline MessageChannel( std::string_view log_channel );

	// Public interface.
	public:
		//
		inline const bool IsEnabled() const;


		//
		inline std::string_view GetRawChannel() const	{ return m_channel; };

		//
		inline std::string GetChannel() const			{ return BufferEncoder::Decode( std::string{ m_channel } ); };


		//
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

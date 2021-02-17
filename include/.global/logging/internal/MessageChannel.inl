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
	template< Black::BuildMode BUILD_CONFIGURATION >
	inline MessageChannel<BUILD_CONFIGURATION>::MessageChannel( std::string_view log_channel )
		: m_id{ GetChannelUniqueId( log_channel ) }
	{
	}

	template< Black::BuildMode BUILD_CONFIGURATION >
	inline const bool MessageChannel<BUILD_CONFIGURATION>::IsEnabled() const
	{
		return IsChannelEnabled( m_id );
	}

	template< Black::BuildMode BUILD_CONFIGURATION >
	inline std::string_view MessageChannel<BUILD_CONFIGURATION>::GetRawChannel() const
	{
		return GetChannel( m_id );
	}

	template< Black::BuildMode BUILD_CONFIGURATION >
	inline std::string MessageChannel<BUILD_CONFIGURATION>::GetChannel() const
	{
		return BufferEncoder::Decode( std::string{ GetRawChannel() } );
	}

	inline MessageChannel<Black::BuildMode::Debug>::MessageChannel( std::string_view log_channel )
		: m_channel{ log_channel }
		, m_id{ GetChannelUniqueId( log_channel ) }
	{
	}

	inline const bool MessageChannel<Black::BuildMode::Debug>::IsEnabled() const
	{
		return IsChannelEnabled( m_id );
	}
}
}
}
}
}

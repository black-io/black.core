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
	inline MessageFormat<BUILD_CONFIGURATION>::MessageFormat( std::string_view format )
		: m_id{ MessageRegistry::GetFormatId( format ) }
	{
	}

	template< Black::BuildMode BUILD_CONFIGURATION >
	inline std::string_view MessageFormat<BUILD_CONFIGURATION>::GetRawFormat() const
	{
		return MessageRegistry::GetFormat( m_id );
	}

	template< Black::BuildMode BUILD_CONFIGURATION >
	inline std::string MessageFormat<BUILD_CONFIGURATION>::GetFormat() const
	{
		return BufferEncoder::Decode( std::string{ GetRawFormat() } );
	}

	inline MessageFormat<Black::BuildMode::Debug>::MessageFormat( std::string_view format )
		: m_format{ format }
		, m_id{ MessageRegistry::GetFormatId( format ) }
	{
	}
}
}
}
}
}

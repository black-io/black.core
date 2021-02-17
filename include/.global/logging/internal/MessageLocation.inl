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
	inline MessageLocation<BUILD_CONFIGURATION>::MessageLocation( std::string_view function_name, std::string_view file_path, const size_t file_line )
		: m_id{ GetLocationUniqueId( function_name, file_path, file_line ) }
	{
	}

	template< Black::BuildMode BUILD_CONFIGURATION >
	inline std::string_view MessageLocation<BUILD_CONFIGURATION>::GetRawFunctionName() const
	{
		return GetFunctionName( m_id );
	}

	template< Black::BuildMode BUILD_CONFIGURATION >
	inline std::string_view MessageLocation<BUILD_CONFIGURATION>::GetRawFilePath() const
	{
		return GetFilePath( m_id );
	}

	template< Black::BuildMode BUILD_CONFIGURATION >
	inline std::string MessageLocation<BUILD_CONFIGURATION>::GetFunctionName() const
	{
		return BufferEncoder::Decode( std::string{ GetRawFunctionName() } );
	}

	template< Black::BuildMode BUILD_CONFIGURATION >
	inline std::string MessageLocation<BUILD_CONFIGURATION>::GetFilePath() const
	{
		return BufferEncoder::Decode( std::string{ GetRawFilePath() } );
	}

	template< Black::BuildMode BUILD_CONFIGURATION >
	inline const size_t MessageLocation<BUILD_CONFIGURATION>::GetFileLine() const
	{
		return GetFileLine( m_id );
	}

	inline MessageLocation<Black::BuildMode::Debug>::MessageLocation( std::string_view function_name, std::string_view file_path, const size_t file_line )
		: m_function_name{ function_name }
		, m_file_path{ file_path }
		, m_file_line{ file_line }
		, m_id{ GetLocationUniqueId( function_name, file_path, file_line ) }
	{
	}
}
}
}
}
}

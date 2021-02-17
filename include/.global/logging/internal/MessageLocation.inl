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
	MessageLocation<BUILD_CONFIGURATION>::MessageLocation( std::string_view function_name, std::string_view file_path, const size_t file_line )
		: m_function_name{ function_name }
		, m_file_path{ file_path }
		, m_file_line{ file_line }
		, m_id{ MessageRegistry::GetLocationId( function_name, file_path, file_line ) }
	{
	}

	MessageLocation<Black::BuildMode::Release>::MessageLocation( std::string_view function_name, std::string_view file_path, const size_t file_line )
		: m_id{ MessageRegistry::GetLocationId( function_name, file_path, file_line ) }
	{
	}

	inline std::string MessageLocation<Black::BuildMode::Release>::GetFunctionName() const
	{
		return BufferEncoder::Decode( std::string{ MessageRegistry::GetFunctionName( m_id ) } );
	}

	inline std::string MessageLocation<Black::BuildMode::Release>::GetFilePath() const
	{
		return BufferEncoder::Decode( std::string{ MessageRegistry::GetFilePath( m_id ) } );
	}

	inline const size_t MessageLocation<Black::BuildMode::Release>::GetFileLine() const
	{
		return MessageRegistry::GetFileLine( m_id );
	}
}
}
}
}
}

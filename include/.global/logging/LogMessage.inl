#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Global
{
inline namespace Logging
{
	inline LogMessage::LogMessage(
		const Category category,
		std::string_view function_name,
		std::string_view file_path,
		const size_t file_line,
		std::string_view log_channel,
		std::string_view format
	)
		: m_id{}
		, m_location_id{}
		, m_channel_id{}
		, m_format_id{}
		, m_category{ category }
	{
	}

	template< typename... TArguments >
	inline void LogMessage::Send( TArguments&&... arguments ) const
	{
		CRET( !IsEnabled() );
	}
}
}
}
}

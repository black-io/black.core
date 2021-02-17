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
		: m_location{ function_name, file_path, file_line }
		, m_channel{ log_channel }
		, m_format_id{}
		, m_category{ category }
		, m_id{ Internal::MessageRegistry::GetMessageUniqueId() }
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

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
		, m_format{ format }
		, m_category{ category }
		, m_id{ Internal::GetMessageUniqueId( *this ) }
	{
	}

	template< typename... TArguments >
	inline void LogMessage::Send( TArguments&&... arguments ) const
	{
		CRET( !IsEnabled() );

		// Perform the sending into attached debugger.
		if constexpr( Black::BUILD_CONFIGURATION == Black::BuildMode::Debug )
		{
			if constexpr( sizeof...( TArguments ) == 0 )
			{
				// In case there is no arguments supplied.
				Black::SendDebuggerMessage( *this, m_format.GetFormat() );
			}
			else
			{
				// {fmt} is permanently included, so may be freely used here. But not the `Black::FormatString`.
				Black::SendDebuggerMessage( *this, fmt::format( m_format.GetFormat(), std::forward<TArguments>( arguments )... ) );
			}
		}

		// Perform the sending binary log.
		// To be continued...
	}
}
}
}
}

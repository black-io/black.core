#include <black/core.h>


namespace Black
{
inline namespace Core
{
inline namespace Global
{
inline namespace Logging
{
	void LogMessage::CloseLogs()
	{
	}

	const bool LogMessage::IsEnabled() const
	{
		const bool is_message_enabled = Internal::IsMessageEnabled( m_id );
		const bool is_channel_enabled = Internal::IsChannelEnabled( *m_channel );
		return is_message_enabled && is_channel_enabled;
	}

	std::string_view LogMessage::GetFunctionName() const
	{
		if constexpr( Black::BUILD_CONFIGURATION == Black::BuildMode::Debug )
		{
			return m_location.GetRawFunctionName();
		}
		else
		{
			return {};
		}
	}

	std::string_view LogMessage::GetFilePath() const
	{
		if constexpr( Black::BUILD_CONFIGURATION == Black::BuildMode::Debug )
		{
			return m_location.GetRawFilePath();
		}
		else
		{
			return {};
		}
	}

	const size_t LogMessage::GetFileLine() const
	{
		if constexpr( Black::BUILD_CONFIGURATION == Black::BuildMode::Debug )
		{
			return m_location.GetFileLine();
		}
		else
		{
			return {};
		}
	}

	std::string_view LogMessage::GetChannel() const
	{
		if constexpr( Black::BUILD_CONFIGURATION == Black::BuildMode::Debug )
		{
			return m_channel.GetRawChannel();
		}
		else
		{
			return {};
		}
	}

	std::string_view LogMessage::GetFormat() const
	{
		if constexpr( Black::BUILD_CONFIGURATION == Black::BuildMode::Debug )
		{
			return m_format.GetRawFormat();
		}
		else
		{
			return {};
		}
	}
}
}
}
}

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
		Internal::MessageRegistry::Close();
	}

	const bool LogMessage::IsEnabled() const
	{
		const bool is_message_enabled = Internal::MessageRegistry::IsMessageEnabled( m_id );
		const bool is_channel_enabled = Internal::MessageRegistry::IsChannelEnabled( *m_channel );
		return is_message_enabled && is_channel_enabled;
	}
}
}
}
}

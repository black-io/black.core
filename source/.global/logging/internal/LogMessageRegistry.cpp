#include <black/core/algorithms.h>

#include "LogMessageRegistry.h"


namespace
{
	/// @brief	Get the thread barrier for synchronized access to registry.
	const Black::Mutex& GetMutex()
	{
		static Black::SpinLock mutex;
		return mutex;
	}

	/// @brief	Get the persistent instance of registry.
	LogMessageRegistry& GetRegistry()
	{
		static LogMessageRegistry registry;
		return registry;
	}

	/// @brief	Build the unique ID using given content of message.
	const LogMessageRegistry::MessageId BuildId( const Black::LogMessage& message )
	{
		// Compress the initial content. Keep the overall algorithm same for purposes of extendability.
		const size_t uuid[]{
			reinterpret_cast<std::uintptr_t>( &message ),
		};

		return static_cast<LogMessageRegistry::MessageId>( Black::GetUnreliableHash( static_cast<const void*>( uuid ), sizeof( uuid ) ) );
	}
}


struct LogMessageRegistry::MessageSlot final
{
	bool is_enabled = true; // Whether the message is able to send log entries.
};


void LogMessageRegistry::SetMessageEnabled( const MessageId message_id, const bool is_enabled )
{
	// Thread-safe access.
	const Black::MutexLock lock{ GetMutex() };
	Black::FindItem( GetRegistry().m_messages_map, message_id ).AndThen(
		[is_enabled]( MessageSlot& slot )
		{
			slot.is_enabled = is_enabled;
		}
	);
}

const LogMessageRegistry::MessageId LogMessageRegistry::GetUniqueId( const Black::LogMessage& message )
{
	const MessageId message_id = BuildId( message );

	LogMessageRegistry& registry = GetRegistry();

	// Thread-safe access.
	const Black::MutexLock lock{ GetMutex() };

	// Check twice the stored channel to be identical.
	if( Black::BUILD_CONFIGURATION == Black::BuildMode::Debug )
	{
		// Regular ENSURES and EXPECTS could not be used in this area due to recursion in logging usage.
		// So only thin debugging constructions may be used.
		if( Black::HasItem( registry.m_messages_map, message_id ) )
		{
			Black::SendDebugString( "Logging message identification looks not unique!" );
			BLACK_DEBUG_BREAK();
		}
	}

	Black::UniqueAdd( registry.m_messages_map, message_id, MessageSlot{} );
	return message_id;
}

const bool LogMessageRegistry::IsMessageEnabled( const MessageId message_id )
{
	bool result = false;

	// Thread-safe access.
	const Black::MutexLock lock{ GetMutex() };
	Black::FindItem( GetRegistry().m_messages_map, message_id ).AndThen(
		[&result]( const MessageSlot& slot )
		{
			result = slot.is_enabled;
		}
	);

	return result;
}

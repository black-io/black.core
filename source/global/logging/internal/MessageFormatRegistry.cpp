#include <black/core/algorithms.h>

#include "MessageFormatRegistry.h"


namespace
{
	/// @brief	Get the thread barrier for synchronized access to registry.
	const Black::Mutex& GetMutex()
	{
		static Black::SpinLock mutex;
		return mutex;
	}

	/// @brief	Get the persistent instance of registry.
	MessageFormatRegistry& GetRegistry()
	{
		static MessageFormatRegistry registry;
		return registry;
	}

	/// @brief	Build the unique ID using given content of format.
	const MessageFormatRegistry::FormatId BuildId( std::string_view format )
	{
		const std::hash<std::string_view> hash{};

		// Compress the initial content. Keep the overall algorithm same for purposes of extendability.
		const size_t uuid[]{
			hash( format ),
		};

		return static_cast<MessageFormatRegistry::FormatId>( Black::GetUnreliableHash( static_cast<const void*>( uuid ), sizeof( uuid ) ) );
	}
}


struct MessageFormatRegistry::FormatSlot final
{
	std::string_view format; // Message format.
};


const MessageFormatRegistry::FormatId MessageFormatRegistry::GetUniqueId( std::string_view format )
{
	const FormatId format_id = BuildId( format );

	MessageFormatRegistry& registry = GetRegistry();

	// Thread-safe access.
	const Black::MutexLock lock{ GetMutex() };

	// Check twice the stored location to be identical.
	if( Black::BUILD_CONFIGURATION == Black::BuildMode::Debug )
	{
		Black::FindItem(
			registry.m_formats_map,
			format_id,
			[&format]( const FormatSlot& slot )
			{
				// Regular ENSURES and EXPECTS could not be used in this area due to recursion in logging usage.
				// So only thin debugging constructions may be used.
				if( slot.format != format )
				{
					Black::SendDebugString( "Message format identification looks not unique!" );
					BLACK_DEBUG_BREAK();
				}
			}
		);
	}

	Black::UniqueAdd( registry.m_formats_map, format_id, FormatSlot{ format } );
	return format_id;
}

std::string_view MessageFormatRegistry::GetFormat( const FormatId format_id )
{
	std::string_view result;

	// Thread-safe access.
	const Black::MutexLock lock{ GetMutex() };
	Black::FindItem(
		GetRegistry().m_formats_map,
		format_id,
		[&result]( const FormatSlot& slot )
		{
			result = slot.format;
		}
	);

	return result;
}

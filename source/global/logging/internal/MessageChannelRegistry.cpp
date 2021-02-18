#include <black/core/algorithms.h>

#include "MessageChannelRegistry.h"


namespace
{
	const Black::Mutex& GetMutex()
	{
		static Black::SpinLock mutex;
		return mutex;
	}

	MessageChannelRegistry& GetRegistry()
	{
		static MessageChannelRegistry registry;
		return registry;
	}

	const MessageChannelRegistry::ChannelId BuildId( std::string_view log_channel )
	{
		std::hash<std::string_view> hash;

		const size_t uuid[]{
			hash( log_channel ),
		};

		return static_cast<MessageChannelRegistry::ChannelId>( Black::GetUnreliableHash( static_cast<const void*>( uuid ), sizeof( uuid ) ) );
	}

	std::string_view GetParentChannel( std::string_view log_channel )
	{
		using Black::Core::Global::Logging::Internal::BufferEncoder;
		for( size_t index = log_channel.size() - 1; index > 1; --index )
		{
			CRET( log_channel[ index ] == BufferEncoder::Encode( '/', index ), log_channel.substr( 0, index ) );
		}

		return {};
	}
}


struct MessageChannelRegistry::ChannelSlot final
{
	std::string_view			channel;
	std::vector<ChannelSlot*>	subchannels;
	bool						is_enabled	= true;
};


void MessageChannelRegistry::SetChannelEnabled( const ChannelId channel_id, const bool is_enabled )
{
	// Thread-safe access.
	const Black::MutexLock lock{ GetMutex() };
	Black::FindItem(
		GetRegistry().m_channels_map,
		channel_id,
		[is_enabled]( ChannelSlot& slot )
		{
			GetRegistry().SetChannelEnabled( slot, is_enabled );
		}
	);
}

const MessageChannelRegistry::ChannelId MessageChannelRegistry::GetUniqueId( std::string_view log_channel )
{
	// Thread-safe access.
	const Black::MutexLock lock{ GetMutex() };
	MessageChannelRegistry& registry = GetRegistry();

	// Check twice the stored channel to be identical.
	if( Black::BUILD_CONFIGURATION == Black::BuildMode::Debug )
	{
		const ChannelId channel_id = BuildId( log_channel );
		Black::FindItem(
			registry.m_channels_map,
			channel_id,
			[&log_channel]( const ChannelSlot& slot )
			{
				// Regular ENSURES and EXPECTS could not be used in this area due to recursion in logging usage.
				// So only thin debugging constructions may be used.
				if( slot.channel != log_channel )
				{
					Black::SendDebugString( "Logging channel identification looks not unique!" );
					BLACK_DEBUG_BREAK();
				}
			}
		);
	}

	return registry.AddChannel( log_channel );
}

std::string_view MessageChannelRegistry::GetChannel( const ChannelId channel_id )
{
	std::string_view result;

	// Thread-safe access.
	const Black::MutexLock lock{ GetMutex() };
	Black::FindItem(
		GetRegistry().m_channels_map,
		channel_id,
		[&result]( const ChannelSlot& slot )
		{
			result = slot.channel;
		}
	);

	return result;
}

const bool MessageChannelRegistry::IsChannelEnabled( const ChannelId channel_id )
{
	bool result = false;

	// Thread-safe access.
	const Black::MutexLock lock{ GetMutex() };
	Black::FindItem(
		GetRegistry().m_channels_map,
		channel_id,
		[&result]( const ChannelSlot& slot )
		{
			result = slot.is_enabled;
		}
	);

	return result;
}

const MessageChannelRegistry::ChannelId MessageChannelRegistry::AddChannel( std::string_view log_channel )
{
	const ChannelId channel_id = BuildId( log_channel );
	CRET( !Black::UniqueAdd( m_channels_map, channel_id, ChannelSlot{ log_channel } ), channel_id );

	ChannelSlot&			channel_slot	= m_channels_map[ channel_id ];
	const std::string_view	parent_channel	= GetParentChannel( log_channel );

	//
	if( parent_channel.empty() )
	{
		Black::UniqueAdd( m_channel_roots, &channel_slot );
	}
	else
	{
		const ChannelId parent_id = AddChannel( parent_channel );
		Black::UniqueAdd( m_channels_map[ parent_id ].subchannels, &channel_slot );
	}

	return channel_id;
}

void MessageChannelRegistry::SetChannelEnabled( ChannelSlot& slot, const bool is_enabled )
{
	slot.is_enabled = is_enabled;
	for( ChannelSlot* subchannel_slot : slot.subchannels )
	{
		SetChannelEnabled( *subchannel_slot, is_enabled );
	}
}

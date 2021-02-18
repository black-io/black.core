#include <black/core/algorithms.h>

#include "MessageLocationRegistry.h"


namespace
{
	const Black::Mutex& GetMutex()
	{
		static Black::SpinLock mutex;
		return mutex;
	}

	MessageLocationRegistry& GetRegistry()
	{
		static MessageLocationRegistry registry;
		return registry;
	}

	const MessageLocationRegistry::LocationId BuildId( std::string_view function_name, std::string_view file_path, const size_t file_line )
	{
		std::hash<std::string_view> hash;

		const size_t uuid[]{
			file_line,
			hash( function_name ),
			hash( file_path ),
		};

		return static_cast<MessageLocationRegistry::LocationId>( Black::GetUnreliableHash( static_cast<const void*>( uuid ), sizeof( uuid ) ) );
	}
}


struct MessageLocationRegistry::LocationSlot final
{
	std::string_view	function_name;
	std::string_view	file_path;
	size_t				file_line;
};


const MessageLocationRegistry::LocationId MessageLocationRegistry::GetUniqueId( std::string_view function_name, std::string_view file_path, const size_t file_line )
{
	const LocationId location_id = BuildId( function_name, file_path, file_line );

	// Thread-safe access.
	const Black::MutexLock lock{ GetMutex() };

	// Check twice the stored location to be identical.
	if( Black::BUILD_CONFIGURATION == Black::BuildMode::Debug )
	{
		Black::FindItem(
			GetRegistry().m_locations_map,
			location_id,
			[&function_name, &file_path, file_line]( const LocationSlot& slot )
			{
				// Regular ENSURES and EXPECTS could not be used in this area due to recursion in logging usage.
				// So only thin debugging constructions may be used.
				if( slot.function_name != function_name )
				{
					Black::SendDebugString( "Message location identification looks not unique!" );
					BLACK_DEBUG_BREAK();
				}

				if( slot.file_path != file_path )
				{
					Black::SendDebugString( "Message location identification looks not unique!" );
					BLACK_DEBUG_BREAK();
				}

				if( slot.file_line != file_line )
				{
					Black::SendDebugString( "Message location identification looks not unique!" );
					BLACK_DEBUG_BREAK();
				}
			}
		);
	}

	Black::UniqueAdd( GetRegistry().m_locations_map, location_id, LocationSlot{ function_name, file_path, file_line } );
	return location_id;
}

std::string_view MessageLocationRegistry::GetFunctionName( const LocationId location_id )
{
	std::string_view result;

	// Thread-safe access.
	const Black::MutexLock lock{ GetMutex() };
	Black::FindItem(
		GetRegistry().m_locations_map,
		location_id,
		[&result]( const LocationSlot& slot )
		{
			result = slot.function_name;
		}
	);

	return result;
}

std::string_view MessageLocationRegistry::GetFilePath( const LocationId location_id )
{
	std::string_view result;

	// Thread-safe access.
	const Black::MutexLock lock{ GetMutex() };
	Black::FindItem(
		GetRegistry().m_locations_map,
		location_id,
		[&result]( const LocationSlot& slot )
		{
			result = slot.file_path;
		}
	);

	return result;
}

const size_t MessageLocationRegistry::GetFileLine( const LocationId location_id )
{
	size_t result = 0;

	// Thread-safe access.
	const Black::MutexLock lock{ GetMutex() };
	Black::FindItem(
		GetRegistry().m_locations_map,
		location_id,
		[&result]( const LocationSlot& slot )
		{
			result = slot.file_line;
		}
	);

	return result;
}

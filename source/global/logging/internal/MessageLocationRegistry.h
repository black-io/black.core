#pragma once


#include <black/core.h>
#include <black/core/concurrency.h>


class MessageLocationRegistry final : private Black::NonTransferable
{
// Public inner types.
public:
	//
	using LocationId = uint32_t;

// Public static interface.
public:
	//
	static const LocationId GetUniqueId( std::string_view function_name, std::string_view file_path, const size_t file_line );

	//
	static std::string_view GetFunctionName( const LocationId location_id );

	//
	static std::string_view GetFilePath( const LocationId location_id );

	//
	static const size_t GetFileLine( const LocationId location_id );

// Private inner types.
private:
	//
	struct LocationSlot;

// Private state.
private:
	std::unordered_map<LocationId, LocationSlot> m_locations_map; //
};
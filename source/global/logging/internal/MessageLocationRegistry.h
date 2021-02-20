#pragma once


#include <black/core.h>
#include <black/core/concurrency.h>


/**
	@brief	Registry implementation to control the source code locations.

	Since the log messages and all it components are persistent entities, this registry is also persistent.
*/
class MessageLocationRegistry final : private Black::NonTransferable
{
// Public inner types.
public:
	/// @brief	Internal type of location ID.
	using LocationId = uint32_t;

// Public static interface.
public:
	/// @brief	Get the unique ID for given location. The value returned is always unique and constant for particular location.
	static const LocationId GetUniqueId( std::string_view function_name, std::string_view file_path, const size_t file_line );

	/// @brief	Get the string buffer of function name for the location by given unique ID.
	static std::string_view GetFunctionName( const LocationId location_id );

	/// @brief	Get the string buffer of source code file path for the location by given unique ID.
	static std::string_view GetFilePath( const LocationId location_id );

	/// @brief	Get the source code line for the location by given unique ID.
	static const size_t GetFileLine( const LocationId location_id );

// Private inner types.
private:
	/// @brief	Slot to store the location information.
	struct LocationSlot;

// Private state.
private:
	std::unordered_map<LocationId, LocationSlot> m_locations_map; // Registered locations.
};
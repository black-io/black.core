#pragma once


#include <black/core.h>
#include <black/core/concurrency.h>


/**
	@brief	Registry implementation to control the message formats.

	Since the log messages and all it components are persistent entities, this registry is also persistent.
*/
class MessageFormatRegistry final : private Black::NonTransferable
{
// Public inner types.
public:
	/// @brief	Internal type of format ID.
	using FormatId = uint32_t;

// Public static interface.
public:
	/// @brief	Get the unique ID for given format. The value returned is always unique and constant for particular format.
	static const FormatId GetUniqueId( std::string_view format );

	/// @brief	Get the string buffer of format by given unique ID.
	static std::string_view GetFormat( const FormatId format_id );

// Private inner types.
private:
	/// @brief	Slot to store the format information.
	struct FormatSlot;

// Private state.
private:
	std::unordered_map<FormatId, FormatSlot> m_formats_map; // Registered formats.
};

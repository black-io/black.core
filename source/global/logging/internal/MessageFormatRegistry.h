#pragma once


#include <black/core.h>
#include <black/core/concurrency.h>


class MessageFormatRegistry final : private Black::NonTransferable
{
// Public inner types.
public:
	//
	using FormatId = uint32_t;

// Public static interface.
public:
	//
	static const FormatId GetUniqueId( std::string_view format );

	//
	static std::string_view GetFormat( const FormatId format_id );

// Private inner types.
private:
	//
	struct FormatSlot;

// Private state.
private:
	std::unordered_map<FormatId, FormatSlot> m_formats_map; //
};

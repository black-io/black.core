#pragma once


#include <black/core.h>
#include <black/core/concurrency.h>


class MessageChannelRegistry final : private Black::NonTransferable
{
// Public inner types.
public:
	//
	using ChannelId = uint32_t;

// Public static interface.
public:
	//
	static void SetChannelEnabled( const ChannelId channel_id, const bool is_enabled );


	//
	static const ChannelId GetUniqueId( std::string_view log_channel );

	//
	static std::string_view GetChannel( const ChannelId channel_id );

	//
	static const bool IsChannelEnabled( const ChannelId channel_id );

// Private inner types.
private:
	//
	struct ChannelSlot;

// Private interface.
private:
	//
	const ChannelId AddChannel( std::string_view log_channel );

	//
	void SetChannelEnabled( ChannelSlot& slot, const bool is_enabled );

// Private state.
private:
	std::unordered_map<ChannelId, ChannelSlot>	m_channels_map;		//
	std::vector<ChannelSlot*>					m_channel_roots;	//
};

#pragma once


#include <black/core.h>
#include <black/core/concurrency.h>


/**
	@brief	Registry implementation to control the message channels.

	Also this registry controls the state of registered channels.

	Since the log messages and all it components are persistent entities, this registry is also persistent.
*/
class MessageChannelRegistry final : private Black::NonTransferable
{
// Public inner types.
public:
	/// @brief	Internal type of channel ID.
	using ChannelId = uint32_t;

// Public static interface.
public:
	/// @brief	Set the state of channel, making it enabled to send the messages or not.
	static void SetChannelEnabled( const ChannelId channel_id, const bool is_enabled );


	/// @brief	Get the unique ID for given channel. The value returned is always unique and constant for particular channel.
	static const ChannelId GetUniqueId( std::string_view log_channel );

	/// @brief	Get the string buffer of channel by given unique ID.
	static std::string_view GetChannel( const ChannelId channel_id );

	/// @brief	Whether the channel with given ID is enabled to send the messages.
	static const bool IsChannelEnabled( const ChannelId channel_id );

// Private inner types.
private:
	/// @brief	Slot to store the channel information.
	struct ChannelSlot;

// Private interface.
private:
	/// @brief	Add the new channel into channel tree.
	const ChannelId AddChannel( std::string_view log_channel );

	/// @brief	Enable or disable the subtree of channels.
	void SetChannelEnabled( ChannelSlot& slot, const bool is_enabled );

// Private state.
private:
	std::unordered_map<ChannelId, ChannelSlot>	m_channels_map;		// Registered channels.
	std::vector<ChannelSlot*>					m_channel_roots;	// List of root channels.
};

#pragma once


#include <black/core.h>
#include <black/core/concurrency.h>


/**
	@brief	Registry implementation to control the log messages.

	Since the log messages and all it components are persistent entities, this registry is also persistent.
*/
class LogMessageRegistry final : Black::NonTransferable
{
// Public inner types.
public:
	/// @brief	Internal type of message ID.
	using MessageId = uint32_t;

// Public static interface.
public:
	/// @brief	Set the state of message, making it enabled to send the log entries or not.
	static void SetMessageEnabled( const MessageId message_id, const bool is_enabled );


	/// @brief	Get the unique ID for given message. The value returned is always unique and constant for particular message.
	static const MessageId GetUniqueId( const Black::LogMessage& message );

	/// @brief	Whether the message with given ID is enabled to send the log entries.
	static const bool IsMessageEnabled( const MessageId message_id );

// Private inner types.
private:
	/// @brief	Slot to store the message information.
	struct MessageSlot;

// Private state.
private:
	std::unordered_map<MessageId, MessageSlot> m_messages_map; // Registered messages.
};

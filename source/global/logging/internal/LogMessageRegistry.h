#pragma once


#include <black/core.h>
#include <black/core/concurrency.h>


class LogMessageRegistry final : Black::NonTransferable
{
// Public inner types.
public:
	//
	using MessageId = uint32_t;

// Public static interface.
public:
	//
	static void SetMessageEnabled( const MessageId message_id, const bool is_enabled );


	//
	static const MessageId GetUniqueId( const Black::LogMessage& message );

	//
	static const bool IsMessageEnabled( const MessageId message_id );

// Private inner types.
private:
	//
	struct MessageSlot;

// Private state.
private:
	std::unordered_map<MessageId, MessageSlot> m_messages_map; //
};

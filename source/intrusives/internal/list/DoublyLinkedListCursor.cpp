#include <black/core/intrusives.h>


namespace Black
{
inline namespace Core
{
inline namespace Intrusives
{
namespace Internal
{
namespace
{
	// Logging channel.
	constexpr const char* LOG_CHANNEL = "Black/Intrusives/DoublyLinkedList/Cursor";
}


	DoublyLinkedListCursor::DoublyLinkedListCursor( DoublyLinkedListCursor&& other ) noexcept
		: m_slot{ std::exchange( other.m_slot, nullptr ) }
	{
	}

	DoublyLinkedListCursor::DoublyLinkedListCursor( DoublyLinkedListSlot* slot ) noexcept
		: m_slot{ slot }
	{
	}

	DoublyLinkedListCursor& DoublyLinkedListCursor::operator=( DoublyLinkedListCursor&& other ) noexcept
	{
		m_slot = std::exchange( other.m_slot, nullptr );
		return *this;
	}

	void DoublyLinkedListCursor::ShiftBack()
	{
		EXPECTS_DEBUG( m_slot != nullptr );
		EXPECTS_DEBUG( m_slot->m_previous != nullptr );
		m_slot = m_slot->m_previous;
	}

	void DoublyLinkedListCursor::ShiftNext()
	{
		EXPECTS_DEBUG( IsValid() );
		m_slot = m_slot->m_next;
	}

	const bool DoublyLinkedListCursor::IsValid() const
	{
		return ( m_slot != nullptr ) && !m_slot->IsEndSlot();
	}

	const bool DoublyLinkedListCursor::IsEnd() const
	{
		return ( m_slot != nullptr ) && m_slot->IsEndSlot();
	}

	DoublyLinkedListSlot& DoublyLinkedListCursor::GetSlot() const
	{
		EXPECTS_DEBUG( IsValid() );
		return *m_slot;
	}
}
}
}
}

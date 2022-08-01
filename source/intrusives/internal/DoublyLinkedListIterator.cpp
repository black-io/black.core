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
	constexpr const char* LOG_CHANNEL = "Black/Intrusives/DoublyLinkedList/Iterator";
}


	DoublyLinkedListIterator::DoublyLinkedListIterator( DoublyLinkedListIterator&& other ) noexcept
		: m_slot{ std::exchange( other.m_slot, nullptr ) }
	{
	}

	DoublyLinkedListIterator::DoublyLinkedListIterator( DoublyLinkedListSlot* slot ) noexcept
		: m_slot{ slot }
	{
	}

	DoublyLinkedListIterator& DoublyLinkedListIterator::operator=( DoublyLinkedListIterator&& other ) noexcept
	{
		m_slot = std::exchange( other.m_slot, nullptr );
		return *this;
	}

	void DoublyLinkedListIterator::ShiftBack()
	{
		EXPECTS_DEBUG( m_slot != nullptr );
		EXPECTS_DEBUG( m_slot->m_previous != nullptr );
		m_slot = m_slot->m_previous;
	}

	void DoublyLinkedListIterator::ShiftNext()
	{
		EXPECTS_DEBUG( IsValid() );
		EXPECTS_DEBUG( m_slot->m_next != nullptr );
		m_slot = m_slot->m_next;
	}

	const bool DoublyLinkedListIterator::IsValid() const
	{
		return ( m_slot != nullptr ) && !m_slot->IsEndSlot();
	}

	const bool DoublyLinkedListIterator::IsEnd() const
	{
		return ( m_slot != nullptr ) && m_slot->IsEndSlot();
	}

	DoublyLinkedListSlot& DoublyLinkedListIterator::GetSlot() const
	{
		EXPECTS_DEBUG( IsValid() );
		return *m_slot;
	}
}
}
}
}

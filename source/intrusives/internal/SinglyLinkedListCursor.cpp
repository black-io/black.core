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
	constexpr const char* LOG_CHANNEL = "Black/Intrusives/SinglyLinkedList/Iterator";
}


	SinglyLinkedListIterator::SinglyLinkedListIterator( SinglyLinkedListIterator&& other ) noexcept
		: m_slot{ std::exchange( other.m_slot, nullptr ) }
	{
	}

	SinglyLinkedListIterator::SinglyLinkedListIterator( SinglyLinkedListSlot* slot ) noexcept
		: m_slot{ slot }
	{
	}

	SinglyLinkedListIterator& SinglyLinkedListIterator::operator=( SinglyLinkedListIterator&& other ) noexcept
	{
		m_slot = std::exchange( other.m_slot, nullptr );
		return *this;
	}

	void SinglyLinkedListIterator::ShiftNext()
	{
		EXPECTS_DEBUG( IsValid() );
		m_slot = m_slot->m_next;
	}

	const bool SinglyLinkedListIterator::IsValid() const
	{
		return ( m_slot != nullptr ) && !m_slot->IsEndSlot();
	}

	const bool SinglyLinkedListIterator::IsEnd() const
	{
		return ( m_slot != nullptr ) && m_slot->IsEndSlot();
	}

	SinglyLinkedListSlot& SinglyLinkedListIterator::GetSlot() const
	{
		EXPECTS_DEBUG( IsValid() );
		return *m_slot;
	}
}
}
}
}

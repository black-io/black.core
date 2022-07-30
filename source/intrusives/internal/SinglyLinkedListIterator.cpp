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
		: m_current_slot{ std::exchange( other.m_current_slot, nullptr ) }
	{
	}

	SinglyLinkedListIterator::SinglyLinkedListIterator( SinglyLinkedListSlot* slot ) noexcept
		: m_current_slot{ slot }
	{
	}

	SinglyLinkedListIterator& SinglyLinkedListIterator::operator=( SinglyLinkedListIterator&& other ) noexcept
	{
		m_current_slot = std::exchange( other.m_current_slot, nullptr );
		return *this;
	}

	void SinglyLinkedListIterator::ShiftNext()
	{
		EXPECTS_DEBUG( IsValid() );
		m_current_slot = m_current_slot->m_next;
	}
}
}
}
}

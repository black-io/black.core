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
	constexpr const char* LOG_CHANNEL = "Black/Intrusives/SinglyLinkedList/Cursor";
}


	SinglyLinkedListCursor::SinglyLinkedListCursor( SinglyLinkedListCursor&& other ) noexcept
		: m_slot{ std::exchange( other.m_slot, nullptr ) }
	{
	}

	SinglyLinkedListCursor::SinglyLinkedListCursor( SinglyLinkedListSlot* slot ) noexcept
		: m_slot{ slot }
	{
	}

	SinglyLinkedListCursor& SinglyLinkedListCursor::operator=( SinglyLinkedListCursor&& other ) noexcept
	{
		m_slot = std::exchange( other.m_slot, nullptr );
		return *this;
	}

	void SinglyLinkedListCursor::ShiftNext()
	{
		EXPECTS_DEBUG( IsValid() );
		m_slot = m_slot->m_next;
	}

	const bool SinglyLinkedListCursor::IsValid() const
	{
		return ( m_slot != nullptr ) && !m_slot->IsEndSlot();
	}

	const bool SinglyLinkedListCursor::IsEnd() const
	{
		return ( m_slot != nullptr ) && m_slot->IsEndSlot();
	}

	SinglyLinkedListSlot& SinglyLinkedListCursor::GetSlot() const
	{
		EXPECTS_DEBUG( IsValid() );
		return *m_slot;
	}
}
}
}
}

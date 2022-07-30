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
	constexpr const char* LOG_CHANNEL = "Black/Intrusives/DoublyLinkedList/Slot";
}


	DoublyLinkedListSlot::DoublyLinkedListSlot( DoublyLinkedListSlot&& other ) noexcept
	{
		CRET( other.IsEndSlot() || !other.IsAttached() );
		other.m_host->InsertBefore( DoublyLinkedListIterator{ &other }, *this );
		other.Detach();
	}

	DoublyLinkedListSlot::~DoublyLinkedListSlot() noexcept
	{
		Detach();
	}

	DoublyLinkedListSlot& DoublyLinkedListSlot::operator=( DoublyLinkedListSlot&& other ) noexcept
	{
		Detach();

		CRET( !other.IsAttached(), *this );
		other.m_host->InsertBefore( DoublyLinkedListIterator{ &other }, *this );
		other.Detach();

		return *this;
	}

	DoublyLinkedListSlot::DoublyLinkedListSlot( DoublyLinkedList& host )
		: m_host{ &host }
	{
	}

	void DoublyLinkedListSlot::Detach()
	{
		CRET( IsEndSlot() || !IsAttached() );
		m_host->Erase( DoublyLinkedListIterator{ this } );
		ENSURES_DEBUG( m_host == nullptr );
		ENSURES_DEBUG( m_previous == nullptr );
		ENSURES_DEBUG( m_next == nullptr );
	}

	const bool DoublyLinkedListSlot::IsEndSlot() const
	{
		CRET( !IsAttached(), false );
		return this == &m_host->m_end;
	}
}
}
}
}

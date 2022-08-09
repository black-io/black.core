#include <black/core/intrusives.h>


namespace Black
{
inline namespace Core
{
inline namespace Intrusives
{
namespace Internal
{
inline namespace List
{
namespace
{
	// Logging channel.
	constexpr const char* LOG_CHANNEL = "Black/Intrusives/DoublyLinkedList/Slot";
}


	DoublyLinkedListSlot::DoublyLinkedListSlot( DoublyLinkedListSlot&& other ) noexcept
	{
		EXPECTS_DEBUG( !other.IsEndSlot() );

		CRET( !other.IsAttached() );
		other.m_host->InsertInstead( other, *this );
	}

	DoublyLinkedListSlot::~DoublyLinkedListSlot() noexcept
	{
		Detach();
	}

	DoublyLinkedListSlot& DoublyLinkedListSlot::operator=( DoublyLinkedListSlot&& other ) noexcept
	{
		EXPECTS_DEBUG( !other.IsEndSlot() );

		Detach();

		CRET( !other.IsAttached(), *this );
		other.m_host->InsertInstead( other, *this );

		return *this;
	}

	DoublyLinkedListSlot::DoublyLinkedListSlot( DoublyLinkedList& host )
		: m_host{ &host }
	{
	}

	void DoublyLinkedListSlot::Reset()
	{
		m_host		= nullptr;
		m_previous	= nullptr;
		m_next		= nullptr;
	}

	void DoublyLinkedListSlot::Detach()
	{
		CRET( IsEndSlot() || !IsAttached() );
		m_host->Erase( *this );
		ENSURES_DEBUG( m_host == nullptr );
		ENSURES_DEBUG( m_previous == nullptr );
		ENSURES_DEBUG( m_next == nullptr );
	}

	inline const bool DoublyLinkedListSlot::IsEndSlot() const
	{
		return ( m_host != nullptr ) && ( this == &m_host->m_end );
	};
}
}
}
}
}

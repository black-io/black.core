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
	constexpr const char* LOG_CHANNEL = "Black/Intrusives/SinglyLinkedList/Slot";
}


	SinglyLinkedListSlot::SinglyLinkedListSlot( SinglyLinkedListSlot&& other ) noexcept
	{
		CRET( !other.IsAttached() );
		other.m_host->InsertBefore( SinglyLinkedListIterator{ &other }, *this );
		other.Detach();
	}

	SinglyLinkedListSlot::~SinglyLinkedListSlot() noexcept
	{
		Detach();
	}

	SinglyLinkedListSlot& SinglyLinkedListSlot::operator=( SinglyLinkedListSlot&& other ) noexcept
	{
		Detach();

		CRET( !other.IsAttached(), *this );
		other.m_host->InsertBefore( SinglyLinkedListIterator{ &other }, *this );
		other.Detach();

		return *this;
	}

	void SinglyLinkedListSlot::Detach()
	{
		CRET( !IsAttached() );
		m_host->Erase( SinglyLinkedListIterator{ this } );
		ENSURES_DEBUG( m_host == nullptr );
		ENSURES_DEBUG( m_next == nullptr );
	}
}
}
}
}

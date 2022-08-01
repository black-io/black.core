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
		EXPECTS_DEBUG( !other.IsEndSlot() );
		CRET( !other.IsAttached() );

		other.m_host->InsertInstead( other, *this );
	}

	SinglyLinkedListSlot::~SinglyLinkedListSlot() noexcept
	{
		Detach();
	}

	SinglyLinkedListSlot& SinglyLinkedListSlot::operator=( SinglyLinkedListSlot&& other ) noexcept
	{
		EXPECTS_DEBUG( !other.IsEndSlot() );

		Detach();

		CRET( !other.IsAttached(), *this );
		other.m_host->InsertInstead( other, *this );

		return *this;
	}

	SinglyLinkedListSlot::SinglyLinkedListSlot( SinglyLinkedList& host )
		: m_host{ &host }
	{
	}

	void SinglyLinkedListSlot::Reset()
	{
		m_host	= nullptr;
		m_next	= nullptr;
	}

	void SinglyLinkedListSlot::Detach()
	{
		CRET( IsEndSlot() || !IsAttached() );
		m_host->Erase( *this );
		ENSURES_DEBUG( m_host == nullptr );
		ENSURES_DEBUG( m_next == nullptr );
	}

	const bool SinglyLinkedListSlot::IsEndSlot() const
	{
		return ( m_host != nullptr ) && ( this == &m_host->m_end );
	}
}
}
}
}

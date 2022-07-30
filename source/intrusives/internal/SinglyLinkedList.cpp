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
	constexpr const char* LOG_CHANNEL = "Black/Intrusives/SinglyLinkedList";
}


	SinglyLinkedList::SinglyLinkedList( SinglyLinkedList&& other ) noexcept
		: m_head{ std::exchange( other.m_head, nullptr ) }
		, m_tail{ std::exchange( other.m_tail, nullptr ) }
		, m_size{ std::exchange( other.m_size, 0 ) }
	{
		for( Slot* slot = m_head; slot != nullptr; slot = slot->m_next )
		{
			slot->m_host = this;
		}
	}

	SinglyLinkedList::~SinglyLinkedList() noexcept
	{
		Clear();
	}

	SinglyLinkedList& SinglyLinkedList::operator=( SinglyLinkedList&& other ) noexcept
	{
		// End the lifetime of current list.
		SinglyLinkedList::~SinglyLinkedList();

		// Start the lifetime of new list by moving the given `other`.
		return *new( this ) SinglyLinkedList{ std::move( other ) };
	}

	void SinglyLinkedList::Clear()
	{
		CRET( IsEmpty() );

		while( m_head != nullptr )
		{
			Slot* slot		= std::exchange( m_head, m_head->m_next );
			slot->m_host	= nullptr;
			slot->m_next	= nullptr;
		}

		m_size = 0;
	}

	void SinglyLinkedList::PushFront( Slot& slot )
	{
		slot.Detach();

		slot.m_next	= std::exchange( m_head, &slot );
		slot.m_host	= this;
		if( m_tail == nullptr )
		{
			m_tail = m_head;
			ENSURES_DEBUG( m_tail->m_next == nullptr );
		}

		++m_size;
	}

	void SinglyLinkedList::PopFront()
	{
		EXPECTS( !IsEmpty() );

		Slot* slot		= std::exchange( m_head, m_head->m_next );
		slot->m_host	= nullptr;
		slot->m_next	= nullptr;

		EXPECTS_DEBUG( m_size > 0 );
		--m_size;

		if( m_head == nullptr )
		{
			m_tail = nullptr;
		}
	}

	void SinglyLinkedList::PushBack( Slot& slot )
	{
		if( m_tail == nullptr )
		{
			PushFront( slot );
			return;
		}

		slot.Detach();

		m_tail->m_next	= &slot;
		m_tail			= &slot;
		slot.m_host		= this;

		++m_size;

		ENSURES_DEBUG( m_tail->m_next == nullptr );
	}

	void SinglyLinkedList::PopBack()
	{
		if( m_head == m_tail )
		{
			PopFront();
			return;
		}

		Iterator pre_tail{ FindPositionBefore( Iterator{ m_tail } ) };

		pre_tail->m_next	= nullptr;
		Slot* slot			= std::exchange( m_tail, pre_tail.GetCurrentSlot() );
		slot->m_host		= nullptr;
		slot->m_next		= nullptr;

		EXPECTS_DEBUG( m_size > 0 );
		--m_size;
	}

	void SinglyLinkedList::InsertBefore( Iterator position, Slot& slot )
	{
		if( position.GetCurrentSlot() == m_head )
		{
			EXPECTS_DEBUG( position->m_host == this );

			PushFront( slot );
			return;
		}

		if( !position.IsValid() )
		{
			PushBack( slot );
			return;
		}

		Iterator pre_position{ FindPositionBefore( position ) };

		slot.Detach();

		slot.m_next	= std::exchange( pre_position->m_next, &slot );
		slot.m_host	= this;

		++m_size;
	}

	void SinglyLinkedList::Erase( Iterator position )
	{
		EXPECTS( position.IsValid() );
		EXPECTS_DEBUG( !IsEmpty() );
		EXPECTS_DEBUG( position->m_host == this );

		if( position.GetCurrentSlot() == m_head )
		{
			PopFront();
			return;
		}

		if( position.GetCurrentSlot() == m_tail )
		{
			PopBack();
			return;
		}

		Iterator pre_position{ FindPositionBefore( position ) };

		pre_position->m_next	= std::exchange( position->m_next, nullptr );
		position->m_host		= nullptr;

		EXPECTS_DEBUG( m_size > 0 );
		--m_size;
	}

	SinglyLinkedList::Slot& SinglyLinkedList::GetFrontSlot() const
	{
		EXPECTS_DEBUG( m_head != nullptr );
		return *m_head;
	}

	SinglyLinkedList::Slot& SinglyLinkedList::GetBackSlot() const
	{
		EXPECTS_DEBUG( m_tail != nullptr );
		return *m_tail;
	}

	SinglyLinkedList::Iterator SinglyLinkedList::FindPositionBefore( Iterator position ) const
	{
		EXPECTS( position.IsValid() );
		EXPECTS_DEBUG( position->m_host == this );
		EXPECTS_DEBUG( !IsEmpty() );

		EXPECTS_DEBUG( position.GetCurrentSlot() != m_head );

		Iterator pre_position{ GetBegin() };
		while( pre_position.IsValid() && ( pre_position->m_next != position.GetCurrentSlot() ) )
		{
			pre_position.ShiftNext();
		}

		ENSURES_DEBUG( pre_position.IsValid() );
		return pre_position;
	}
}
}
}
}

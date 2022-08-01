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
	constexpr const char* LOG_CHANNEL = "Black/Intrusives/DoublyLinkedList";
}


	DoublyLinkedList::DoublyLinkedList( DoublyLinkedList&& other ) noexcept
		: m_head{ std::exchange( other.m_head, &other.m_end ) }
		, m_size{ std::exchange( other.m_size, 0 ) }
	{
		EXPECTS_DEBUG( m_head != nullptr );
		if( m_head == &other.m_end )
		{
			// Empty list moved.
			m_head = &m_end;
			return;
		}

		Slot* const tail = std::exchange( other.m_end.m_previous, nullptr );

		// Update the link to hosted list for each slot.
		for( Slot* slot = m_head; slot != &other.m_end; slot = slot->m_next )
		{
			ENSURES_DEBUG( slot != nullptr );
			slot->m_host = this;
		}

		// Update the tail slot to link with new end slot.
		tail->m_next = &m_end;
	}

	DoublyLinkedList::~DoublyLinkedList() noexcept
	{
		Clear();
	}

	DoublyLinkedList& DoublyLinkedList::operator=( DoublyLinkedList&& other ) noexcept
	{
		// End the lifetime of current list.
		DoublyLinkedList::~DoublyLinkedList();

		// Start the lifetime of new list by moving the given `other`.
		return *new( this ) DoublyLinkedList{ std::move( other ) };
	}

	void DoublyLinkedList::Clear()
	{
		CRET( IsEmpty() );

		EXPECTS_DEBUG( m_head != nullptr );
		while( !IsEmpty() )
		{
			Slot* slot = std::exchange( m_head, m_head->m_next );
			EXPECTS_DEBUG( m_head != nullptr );

			slot->Reset();
		}

		m_end.m_previous	= nullptr;
		m_size				= 0;
	}

	void DoublyLinkedList::PushFront( Slot& slot )
	{
		slot.Detach();
		ENSURES_DEBUG( slot.m_previous == nullptr );

		m_head->m_previous	= &slot;
		slot.m_host			= this;
		slot.m_next			= std::exchange( m_head, &slot );

		++m_size;
	}

	void DoublyLinkedList::PopFront()
	{
		EXPECTS( !IsEmpty() );

		Slot* slot = std::exchange( m_head, m_head->m_next );

		m_head->m_previous = nullptr;
		slot->Reset();

		EXPECTS_DEBUG( m_size > 0 );
		--m_size;
	}

	void DoublyLinkedList::PushBack( Slot& slot )
	{
		if( IsEmpty() )
		{
			PushFront( slot );
			return;
		}

		slot.Detach();

		Slot* tail			= m_end.m_previous;
		tail->m_next		= &slot;
		slot.m_previous		= tail;
		slot.m_host			= this;
		slot.m_next			= &m_end;
		m_end.m_previous	= &slot;

		++m_size;
	}

	void DoublyLinkedList::PopBack()
	{
		EXPECTS( !IsEmpty() );

		if( m_head == m_end.m_previous )
		{
			PopFront();
			return;
		}

		Slot* const tail		= m_end.m_previous;
		Slot* const new_tail	= tail->m_previous;
		tail->Reset();

		m_end.m_previous		= new_tail;
		new_tail->m_next		= &m_end;

		EXPECTS_DEBUG( m_size > 0 );
		--m_size;
	}

	void DoublyLinkedList::Insert( Iterator position, Slot& slot )
	{
		if( position.IsEnd() )
		{
			PushBack( slot );
			return;
		}

		EXPECTS_DEBUG( !IsEmpty() );
		EXPECTS_DEBUG( position.IsValid() );
		EXPECTS_DEBUG( position->m_host == this );

		if( position.QuerySlot() == m_head )
		{
			PushFront( slot );
			return;
		}

		slot.Detach();

		Slot* const slot_after	= position.QuerySlot();
		Slot* const slot_before	= position->m_previous;

		slot.m_host					= this;
		slot.m_previous				= std::exchange( slot_after->m_previous, &slot );
		slot.m_next					= std::exchange( slot_before->m_next, &slot );

		++m_size;
	}

	void DoublyLinkedList::Erase( Iterator position )
	{
		EXPECTS_DEBUG( !IsEmpty() );
		EXPECTS_DEBUG( position.IsValid() );
		EXPECTS_DEBUG( position->m_host == this );

		if( position.QuerySlot() == m_head )
		{
			PopFront();
			return;
		}

		Erase( *position );

		EXPECTS_DEBUG( m_size > 0 );
		--m_size;
	}

	DoublyLinkedList::Slot& DoublyLinkedList::GetFrontSlot() const
	{
		EXPECTS_DEBUG( !IsEmpty() );
		return *m_head;
	}

	DoublyLinkedList::Slot& DoublyLinkedList::GetBackSlot() const
	{
		EXPECTS_DEBUG( !IsEmpty() );
		return *m_end.m_previous;
	}

	void DoublyLinkedList::InsertInstead( Slot& old_slot, Slot& new_slot )
	{
		Slot* const slot_before	= old_slot.m_previous;
		Slot* const slot_after	= old_slot.m_next;
		slot_before->m_next		= &new_slot;
		slot_after->m_previous	= &new_slot;
		old_slot.Reset();

		new_slot.m_host			= this;
		new_slot.m_previous		= slot_before;
		new_slot.m_next			= slot_after;
	}

	void DoublyLinkedList::Erase( Slot& slot )
	{
		Slot* const slot_after	= slot.m_next;
		Slot* const slot_before	= slot.m_previous;
		slot.Reset();

		slot_before->m_next		= slot_after;
		slot_after->m_previous	= slot_before;
	}
}
}
}
}
